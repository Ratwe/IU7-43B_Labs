#!/bin/bash

file_a=$1
file_b=$2

string_a=$(echo -v "$(cat "$file_a")" | grep -oE "Result: .*")
string_b=$(echo -v "$(cat "$file_b")" | grep -oE "Result: .*")

if [[ "$string_a" == "$string_b"  ]]; then
	exit 0
else
	exit 1
fi
