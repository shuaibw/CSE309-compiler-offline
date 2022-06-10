#!/usr/bin/env bash
if [[ $# -eq 0 ]]; then
    echo "Usage: ./lexrunner.sh"
    exit 1
fi
if [[ -z "$2" ]]; then
    echo "No input file supplied"
    exit 1
fi

flex -o tmp.c "$1"
g++ tmp.c -lfl -o tmp.out
rm tmp.c
./tmp.out "$2"
