#!/bin/bash

if [ $# -lt 3 ]; then
    echo "Usage: $0 <N> <M> <H>"
    exit 1
fi

cd build
cmake .. -D__N=$1 -D__M=$2 -D__H=$3
cmake --build .
