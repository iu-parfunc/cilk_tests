#!/bin/bash

set -xe

export LD_LIBRARY_PATH=$HOME/opt/lib:$LD_LIBRARY_PATH
export PATH=$HOME/opt/bin:$PATH
export C_INCLUDE_PATH=$HOME/opt/include:$C_INCLUDE_PATH

source ../../../build_scripts/env_cilk
source ../../../build_scripts/set_up_cilk_iu

$*
