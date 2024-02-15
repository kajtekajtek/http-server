#!/bin/bash
# client.sh script - test single connection 
# usage: client.sh [file name]
# connect to the server by netcat and send message from a file

# get server port number declared by PORT macro in include/networking.h
get_port_number () 
{
	local port_number=$(cat include/include.h | grep "#define PORT" \
		| cut -d " " -f 3)

	if [ $port_number -lt 0 ]; then
		echo "Invalid port number declared in include/networking.h"
		exit 1
	fi
	
	echo "$port_number"
}

# command line args count check
if [ $# != 1 ]; then
	echo "usage: client.sh [file name]"
	exit 1
fi

msg_file_name=$1 # file with the client message
port_number="$(get_port_number)"

# file path checking
if ! [ -f $msg_file_name ]; then
	echo "$file_name is not a file!"
	exit 1
fi

# connect to localhost on port $port_number and send message from
# $file_name file
echo "Connecting to localhost on port $port_number"
echo -e "Response:\n"
time nc -N 127.0.0.1 $port_number < $msg_file_name
echo -e "\n\nDone\n"
