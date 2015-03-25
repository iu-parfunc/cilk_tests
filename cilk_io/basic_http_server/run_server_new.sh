#!/bin/bash
BENCH=$*
for c in 1 8 16 64 128 256 512 1024 2048 4096; do for i in `seq 5`; do $BENCH; sleep 1; done; done
