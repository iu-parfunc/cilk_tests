#!/bin/bash

set -e

rm -rf build
mkdir build 
cd build 
DIR_BIN=.

echo "Where is cmake?  Here: "`which -a cmake`

cmake \
  -DCONCURRENT_CILK=ON \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_INSTALL_PREFIX=$DIR_BIN ..;

echo "CMake complete, exit code was $?"

# For whatever reason "make && make install" leads to great trouble here:
make 
make install

cd ..

