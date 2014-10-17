#!/bin/bash

set -x

MYPATH=`dirname $0`

WHICHSERVER=$1
NUMWORKERS=$2
PORT=$3

PBS_NNODES=`cat $PBS_NODEFILE | wc -l`;
NUM_CLIENTS=$((PBS_NNODES-1))

SERVER_HOSTNAME=`sed "$PBS_NNODES"'q;d' $PBS_NODEFILE`
SERVER_IP=`getent hosts | grep -m 1 $SERVER_HOSTNAME | awk '{printf $1}'`

echo "Spawning 1 server and $NUM_CLIENTS client(s)"

pbsdsh -n $NUM_CLIENTS $MYPATH/$WHICHSERVER $NUMWORKERS $PORT
sleep 1
pbsdsh -c $NUM_CLIENTS weighttp -n 100000 -c 128 -k $SERVER_IP:$PORT
