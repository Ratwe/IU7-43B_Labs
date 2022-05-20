#!/bin/bash

names=(main transp_main)
opts=(Os O0 O1 O2 O3)
sizes=(1 2 3 4 5 6 7 8 9 10)

one_size=10
until [ $one_size -eq 100 ]; do
	one_size=$((one_size + 5))
	sizes+=("$one_size")
done

counter=0
total=10

for name in "${names[@]}"; do
	echo -n -e "BUILDING_APPS: $counter/$total \r"
	for opt in "${opts[@]}"; do
		for size in "${sizes[@]}"; do
			gcc -std=c99 -Wall -Werror -Wextra -Wpedantic\
			-DMAX_SIZE="$size" \
			-"$opt" \
			../programms/"$name".c -o ../apps/app_"$name"_"$opt"_"$size".exe
		done	
		counter=$((counter+1))
		echo -n -e "BUILDING_APPS: $counter/$total \r"
	done
done
