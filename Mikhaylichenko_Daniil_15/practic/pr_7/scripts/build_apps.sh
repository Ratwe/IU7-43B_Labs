#!/bin/bash

names=(idx exp pnt)
opts=(Os O0 O1 O2 O3)
sizes=(1 2 3 4 5 6 7 8 9 10 25 50 100)

one_size=0
until [ $one_size -eq 10000 ]; do
	one_size=$((one_size + 500))
	sizes+=("$one_size")
done

counter=0
total=15
percent=$((counter * 100 / total))

for name in "${names[@]}"; do
	echo -n -e "\t\033[36mBUILDING APPS: "$percent"/100%\033[0m \r"
	for opt in "${opts[@]}"; do
		for size in "${sizes[@]}"; do
			gcc -std=c99 -Wall -Werror -Wextra -Wpedantic\
			-DMAX_SIZE="$size" \
			-"$opt" \
			../programms/"$name".c -o ../apps/app_"$name"_"$opt"_"$size".exe
		done	
		counter=$((counter+1))
		percent=$((counter * 100 / total))
		echo -n -e "\t\033[36mBUILDING APPS: "$percent"/100%\033[0m \r"
	done
done

echo -e "\t\033[32mCOMPLETE BUILDING APPS \033[0m"
