#! /usr/bin/env python 

# This script is run from CILK_ROOT
import os
import glob
import sys

failed = 0
failed_tests = []

failed_builds = 0
failed_build_dirs = []

known_testfails = [
   './cilk_tests/parfibbin/ivars_parfib.exe',
   './cilk_tests/parfibbin/fib_pthread.exe',
   './cilk_tests/cilk_io/basic_http_serverbin/naive_server_pthread.exe',
   './cilk_tests/cilk_io/basic_http_serverbin/pthread_server_base.exe',
   './cilk_tests/cilk_io/basic_http_serverbin/naive_server_cilk.exe',
   './cilk_tests/cilk_io/basic_http_serverbin/cilk_server1.exe',
   './cilk_tests/ivar/benchmarks/pingpongbin/pingpong_ivars.exe']

known_buildfails = [
   './cilk_tests/cilk_io/distfib',
   './cilk_tests/cilk_io/hello_world',
   './cilk_tests/cilk_io/echoserver' ]

ignored_fails = []
  
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
      code = os.system("make -B") # Remake everything
      if code != 0:
        if root in known_buildfails:
          print "Test failed to build, but IGNORING, because it's a known failure: " + root
          ignored_fails.append(root)
        else:
          failed_builds += 1
          failed_build_dirs.append(root)
      for exe in glob.glob("bin/*.exe"): # we either installed in bin/
        print "Running test: ", exe
        ret_code = os.system("timeout 10s " + exe)
        if ret_code != 0:
          if root+exe in known_testfails:
            print "Test failed to run, but IGNORING, because it's a known failure: " + root+exe
            ignored_fails.append(root)
          else:
            failed += 1
            failed_tests.append(root + exe)
    finally:
      os.chdir(cwd)

print "================== Tests Finished ========================"
print "Number of unexpected failed tests  : ", failed
print "Tests that failed       : ", failed_tests
print "Number of unexpected failed builds : ", failed_builds
print "Builds that failed      : ", failed_build_dirs
print "=========================================================="

if len(ignored_fails) > 0:
  print "WARNING: IGNORED known failures: "
  print ignored_fails

if failed_builds != 0 or failed != 0:
  sys.exit(1)
