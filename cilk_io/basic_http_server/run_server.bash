#!/bin/bash

HOST=$1
NAME=$2
NUM_WORKERS=$3
NUM_REQUESTS=$4
PORT_NUM=$(shuf -i 60000-90000 -n 1)

echo ./bin/$NAME $NUM_WORKERS $PORT_NUM &
./bin/$NAME $NUM_WORKERS $PORT_NUM &

# Wait for the server to start running
sleep 1

echo weighttp -n $NUM_REQUESTS -k 129.79.247.33:$PORT_NUM

ssh $HOST "

weighttp -n $NUM_REQUESTS -k 129.79.247.33:$PORT_NUM

"
