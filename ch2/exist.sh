#!/bin/bash

# check use supplied argument
if [ "$#" -ne 1 ]; then
    echo "You must supply exactly one argument."
    echo "Example: $0 /etc"
    exit 1
fi

# Check if file/directory exists
test -e "$1"
if [ "$?" -eq 0 ]; then
    echo "File or directory exists"
elif [ "$?" -eq 1 ]; then
    echo "File or directory does not exists"
    exit 3 # we specify special code so it is known it does not exist
else
    echo "Unknown return value from test..."
    exit
fi

exit 0

