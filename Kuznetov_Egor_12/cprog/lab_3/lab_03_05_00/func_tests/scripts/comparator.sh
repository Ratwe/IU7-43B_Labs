#!/bin/bash
if [ $# -ne 2 ]; then
    echo "Need 2 files to compare" >&2
    exit 3
fi

if [ ! -f "$1" ]; then
    echo "File '$1' not exist" >&2
    exit 2
fi
if [ ! -f "$2" ]; then
    echo "File '$2' not exist" >&2
    exit 2
fi

value_1=$(grep -oE "\-?[0-9]+\.?[0-9]*" "$1")
value_2=$(grep -oE "\-?[0-9]+\.?[0-9]*" "$2")

if [ "$value_1" != "$value_2" ]; then
    exit 1
fi
exit 0
