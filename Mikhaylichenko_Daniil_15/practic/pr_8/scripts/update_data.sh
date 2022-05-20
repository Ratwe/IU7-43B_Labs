#!/bin/bash

names=(main transp_main)
opts=(Os O0 O1 O2 O3)
sizes=(1 2 3 4 5 6 7 8 9 10)

one_size=10
until [ $one_size -eq 100 ]; do
	one_size=$((one_size + 5))
	sizes+=("$one_size")
done

total=1

if [ -n "$1" ]; then
	total=$1
fi

for counter in $(seq "$total"); do
	for name in "${names[@]}"; do
		for opt in "${opts[@]}"; do
	       	for size in "${sizes[@]}"; do
				echo -n -e "UPDATING_DATA: $counter/$total \r"
				../apps/app_"$name"_"$opt"_"$size".exe \
				>> ../data/"$name"_"$opt"_"$size".txt
			done
		done
	done
done

