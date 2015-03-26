#!/bin/bash
variant=$*
set -x
for c in 16 32 64 128 256 512 1024 2048 4096; do for i in `seq 5`; do weighttp -n 100000 -c $c -t 16 -k 192.168.1.12:6600 ; sleep 2; done >> ${variant}_$c.dat; done
