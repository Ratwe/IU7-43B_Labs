#!/bin/bash

file_a=$1
file_b=$2

nums_a=$(echo -v "$(cat "$file_a")" | grep -oE "[0-9]{1,}" | tr '\n' ' ' | tr -d '[:space:]')
nums_b=$(echo -v "$(cat "$file_b")" | grep -oE "[0-9]{1,}" | tr '\n' ' ' | tr -d '[:space:]')

if [[ "$nums_a" == "$nums_b" ]] && [[ "$nums_a" != "" ]]; then
	exit 0
else
	exit 1
fi
