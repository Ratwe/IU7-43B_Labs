#!/bin/bash

#Считывание позиционных параметров
output=$1
number=$2 
mode=$3

#Сравнение двух файлов
if [ $mode -eq 0 ]; then
	echo "Result: " > temp.txt
	cat out.txt >> temp.txt
	cat temp.txt | tr -d '\n' > out.txt
	eval rm temp.txt
	
	if diff -w $output out.txt 1>/dev/null; then
		echo -e "		\033[33mPOS TEST$number: \033[32mpass\033[0m"
	else
		echo -e "		\033[33mPOS TEST$number: \033[31mfailed\033[0m"
	fi
else
	if [ $output -ne 0 ]; then
		echo -e "		\033[33mNEG TEST$number: \033[32mpass\033[0m"
	else
		echo -e "		\033[33mNEG TEST$number: \033[33mfailed\033[0m"
	fi
fi
