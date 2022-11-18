#!/bin/bash

test_out=$1
dirty_out=$2

sed -e 's/[^-0-9.]//g' "$dirty_out" > clear_out.txt
clear_out=clear_out.txt

if diff -w "$test_out" "$clear_out" 1>/dev/null; then
	exit 0
else
	exit 2
fi
