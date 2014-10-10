#!/bin/bash

set -xe

# No reason to do anything sophisticated here because if things
# progress further we should move tests into the proper ICL test
# suite.

# set -e 
RUNARGS=$1

for test in `ls bin | grep .exe`; do 
  ./bin/$test $RUNARGS
done
