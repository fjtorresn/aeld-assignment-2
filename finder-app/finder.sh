#!/bin/bash

if [ -z "$1" ]; then
    echo "Finder requires 2 arguments: filesdir is missing."
    exit 1
fi
if [ -z "$2" ]; then
    echo "Finder requires 2 arguments: searchstr is missing."
    exit 1
fi
if [ ! -d "$1" -a "$1" != ".." -a "$1" != "." ]; then
    echo "Filesdir must be a valid directory"
    exit 1
fi

X=$(($(ls -l $1 | wc -l)-1))
Y=$(grep $2 $1 -r | wc -l)

echo "The number of files are $X and the number of matching lines are $Y"

exit 0


