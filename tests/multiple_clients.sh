#!/bin/bash

msg_file_name=$1 # file with the client message

if [ $# != 2 ] || ! [[ $2 =~ ^[0-9]+$ ]]; then
	echo "Usage: multiple_clients.sh [file] [number of connections]"
	exit 1;
fi

for (( i=1; i <= $2; i++ )); do
	echo $i
	time tests/client.sh $msg_file_name
done
