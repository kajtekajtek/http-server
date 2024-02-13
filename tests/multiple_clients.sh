#!/bin/bash

if [ $# != 1 ] || ! [[ $1 =~ ^[0-9]+$ ]]; then
	echo "Usage: multiple_clients.sh [number of connections]"
	exit 1;
fi

for (( i=1; i <= $1; i++ )); do
	echo $i
	tests/client.sh tests/test_msg.txt
done
