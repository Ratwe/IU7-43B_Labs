#!/bin/bash

file_a=$1
file_b=$2

#echo file_a $(cat $file_a)
#echo file_ b $(cat $file_b)

nums_a=$(echo -v "$(cat "$file_a")" | grep -oE "[0-9]{1,}" | tr '\n' ' ' | tr -d '[:space:]')
nums_b=$(echo -v "$(cat "$file_b")" | grep -oE "[0-9]{1,}" | tr '\n' ' ' | tr -d '[:space:]')

#echo a: $nums_a
#echo b: $nums_b

if [[ "$nums_a" == "$nums_b"  ]]; then
	echo 0
else
	echo 1
fi
