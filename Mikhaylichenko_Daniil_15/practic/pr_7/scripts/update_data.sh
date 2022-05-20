#!/bin/bash

names=(idx exp pnt)
opts=(Os O0 O1 O2 O3)
sizes=(1 2 3 4 5 6 7 8 9 10 25 50 100)

one_size=0
until [ $one_size -eq 10000 ]; do
	one_size=$((one_size + 500))
	sizes+=("$one_size")
done

total=1

if [ ! -z $1 ]; then
	total=$1
fi

echo -n -e "\t\033[36mUPDATING DATA: 0/100%\033[0m \r"

for counter in $(seq "$total"); do
	for name in "${names[@]}"; do
		for opt in "${opts[@]}"; do
	       	for size in "${sizes[@]}"; do
	       		percent=$((counter * 100 / total))
				echo -n -e "\t\033[36mUPDATING DATA: $percent/100%\033[0m \r"
				../apps/app_"$name"_"$opt"_"$size".exe \
				>> ../data/"$name"_"$opt"_"$size".txt
			done
		done
	done
done

echo -e "\t\033[32mCOMPLETE UPDATING APPS \033[0m"