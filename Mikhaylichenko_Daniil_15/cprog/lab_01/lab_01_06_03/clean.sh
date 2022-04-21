#!/bin/bash

temp=("main.i" "main.o" "main.s" "a.out")

for i in "${temp[@]}"; do
	command="rm -f $i"
	eval "$command"
done
