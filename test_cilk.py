#! /usr/bin/env python 

# This script is run from CILK_SRC
import os
import glob
import sys
from subprocess import Popen, PIPE

class colors:
  SUCCESS = '\033[92m'
  FAIL = '\033[91m'
  ENDC = '\033[0m'

def printcolor(stdout, stderr):
  print "---------------------------------------------"
  print colors.FAIL,"STDERR output: ",err,colors.ENDC
  print "STDOUT output: "
  print "---------------------------------------------"

passed = 0

failed = 0
failed_tests = []

failed_builds = 0
failed_build_dirs = []

known_testfails = [
   './cilk_tests/parfib/bin/ivars_parfib.exe',
   './cilk_tests/parfib/bin/fib_pthread.exe',
   './cilk_tests/ivar/benchmarks/microbench/bin/microbench_many_blocking.exe',
   './cilk_tests/cilk_io/basic_http_server/bin/naive_server_pthread.exe',
   './cilk_tests/cilk_io/basic_http_server/bin/pthread_server_base.exe',
   './cilk_tests/cilk_io/basic_http_server/bin/naive_server_cilk.exe',
   './cilk_tests/cilk_io/basic_http_server/bin/cilk_server1.exe',
   './cilk_tests/ivar/benchmarks/pingpong/bin/pingpong_ivars.exe']

known_buildfails = [
   './cilk_tests/cilk_io/distfib',
   './cilk_tests/cilk_io/hello_world',
   './cilk_tests/cilk_io/echoserver' ,
   # Added after exposing silent failed builds:
   './cilk_tests/ivar/benchmarks/wavefront',
   './cilk_tests/ivar/libs/io/iotest',
   './cilk_tests/ivar/benchmarks/server/cilk/distPfib' ]

ignored_fails = []

cwd = os.getcwd()
os.chdir(os.environ['CILK_SRC'])
  
for root, dirs, files in os.walk("./cilk_tests/"):
  # Don't go into .git directories
  # or the auto generated "build" dirs
  make_huh = False
  notest = False
  if (".git" not in root and "build" not in root and "pbbs" not in root):
    for file in files: 
      if file == "Makefile": # Have Makefile?
        make_huh = True
      if file == "NOTEST": # Should we test this directory?
        make_huh = False
        notest = True
        break
  if make_huh and not notest:
    cwd = os.getcwd() # get current directory
    try:
      os.chdir(root)
      print "BUILDING in dir: ", root
      proc = Popen("make -B", stderr=PIPE, stdout=PIPE, shell=True)
      out,err = proc.communicate()
      if proc.returncode != 0:
        if root in known_buildfails:
          print "Test failed to build, but IGNORING, because it's a known failure: " + root
          ignored_fails.append(root)
          printcolor(out,err)
        else:
          failed_builds += 1
          failed_build_dirs.append(root)
          printcolor(out,err)
      for exe in glob.glob("/bin/*.exe"): # we either installed in bin/
        print "Running test: ", exe
        ret_code = os.system("timeout 10s " + exe)
        proc = Popen("make -B", stderr=PIPE, stdout=PIPE, shell=True)
        out,err = proc.communicate()
        if proc.returncode == 0:
          passed += 1
        else:
          if root+exe in known_testfails:
            print "Test failed to run, but IGNORING, because it's a known failure: " + root+exe
            ignored_fails.append(root)
            printcolor(out,err)
          else:
            failed += 1
            failed_tests.append(root + exe)
            printcolor(out,err)
    finally:
      os.chdir(cwd)

print "================== Tests Finished ========================"
print "Tests passed : ", passed
print "Number of unexpected failed tests  : ", failed
print "Tests that failed       : ", failed_tests
print "Number of unexpected failed builds : ", failed_builds
print "Builds that failed      : ", failed_build_dirs
print "=========================================================="

if len(ignored_fails) > 0:
  print "WARNING: IGNORED known failures: "
  print ignored_fails

if failed_builds > 0:
    sys.exit(1)
  
if failed > 0:
  if os.getenv("CONCURRENTCILK_CC","icc"):
    print "WARNING: not failing tests because we EXPECT icc to fail for now."
    sys.exit(0)
  else:
    sys.exit(1)


