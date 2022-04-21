#!/bin/bash

valgrind() {
	while true
	do
		read -p "Хотите использовать valgrind? [Д/Н]: " answer
		if [ "$answer" == "Д" -o "$answer" == "д" ]; then
			USE_VALGRIND=0
			break
		elif [ "$answer" == "Н" -o "$answer" == "н" ]; then
			USE_VALGRIND=1
			break
		fi
	done
}

#Настройка директорий
directory=`pwd`
work_directory=${directory%func_tests*}
data="/func_tests/data"
data_directory="$work_directory$data"
pos="/func_tests/scripts/pos_case.sh"
pos_case_file="$directory$pos"
neg="/func_tests/scripts/neg_case.sh"
neg_case_file="$directory$neg"

#Счёт количества позитивных тестов
pos_count=0
for file in `find $data_directory -type f -name "pos_*_in.txt"`; do
	pos_count=$((pos_count+1))
done

#Счёт количества негативных тестов
neg_count=0
for file in `find $data_directory -type f -name "neg_*_in.txt"`; do
	neg_count=$((neg_count+1))
done

echo "START TESTING"

valgrind
#Запуск позитвных тестов
if [ $pos_count -ne 0 ]; then
	echo "	Running positive tests..."
	all=$pos_count+1
	until [ $pos_count -eq 0 ]; do
		number=$((all-pos_count))
		file_stream_in="pos_0"$number"_in.txt"
		file_stream_out="pos_0"$number"_out.txt"
		$pos_case_file $file_stream_in $file_stream_out $number $USE_VALGRIND
		pos_count=$((pos_count-1))
	done
fi

#Запуск негативных тестов
if [ $neg_count -ne 0 ]; then
	echo "	Running negetive tests..."
	all=$neg_count+1
	until [ $neg_count -eq 0 ]; do
		number=$((all-neg_count))
		file_stream_in="neg_0"$number"_in.txt"
		$neg_case_file $file_stream_in $number $USE_VALGRIND
		neg_count=$((neg_count-1))
	done
fi

echo "END TESTING"
