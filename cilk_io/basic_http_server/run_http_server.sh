#!/bin/bash

set -x

eval `modulecmd bash add openmpi`

MYPATH=`dirname $0`

WHICHSERVER=$1
NUMWORKERS=$2
PORT=$3

PBS_NNODES=`cat $PBS_NODEFILE | wc -l`;
NUM_CLIENTS=$((PBS_NNODES-1))

SERVER_HOSTNAME=`sed "$PBS_NNODES"'q;d' $PBS_NODEFILE`
SERVER_IP=`getent hosts | grep -m 1 $SERVER_HOSTNAME | awk '{printf $1}'`

echo "Spawning 1 server and $NUM_CLIENTS client(s)"

#pbsdsh -v -n $NUM_CLIENTS $PWD/run_with_env.sh $LD_LIBRARY_PATH $PATH $PWD/$WHICHSERVER $NUMWORKERS $PORT
#sleep 1
pbsdsh -v -c $NUM_CLIENTS $PWD/run_with_env.sh $LD_LIBRARY_PATH $PATH weighttp -n 1000 -c 16 -t 16 -k $SERVER_IP:$PORT
