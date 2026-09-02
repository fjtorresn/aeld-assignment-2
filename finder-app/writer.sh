#!/bin/bash

if [ -z "$1" ]; then
    echo "Writer requires 2 arguments: writefile is missing."
    exit 1
fi
if [ -z "$2" ]; then
    echo "Writer requires 2 arguments: writestr is missing."
    exit 1
fi

mkdir -p "$(dirname "$1")"

if [ -d "$(dirname "$1")" ]; then
    echo "$2" > "$1"
    exit 0
else
    echo "$1 could not be created"
    exit 1
fi