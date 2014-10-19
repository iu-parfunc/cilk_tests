#!/bin/bash

set -x

export LD_LIBRARY_PATH=$1:$LD_LIBRARY_PATH
shift
export PATH=$1:$PATH
shift

$*
