#!/bin/bash

set -x
set -e

# No reason to do anything sophisticated here because if things
# progress further we should move tests into the proper ICL test
# suite.

# set -e 
RUNARGS=$1

EXES=`ls bin | grep .exe`

if [ "$EXES" == "" ]; then 
  echo 'Error: no binaries found!'
  exit 1;
fi

for test in $EXES; do 
  ./bin/$test $RUNARGS
done
