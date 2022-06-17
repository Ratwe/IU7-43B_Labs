#!/bin/bash

test_out=$1
dirty_out=$2

cat "$dirty_out" > clear_out.txt
clear_out=clear_out.txt

if diff "$test_out" "$clear_out"; then # 1>/dev/null; then
	exit 0
else
	exit 2
fi
