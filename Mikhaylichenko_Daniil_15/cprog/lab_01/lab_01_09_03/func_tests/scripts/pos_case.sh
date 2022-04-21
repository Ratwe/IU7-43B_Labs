#!/bin/bash

#Считывание позиционных параметров
in_file=$1
out_file=$2
number=$3
USE_VALGRIND=$4

#Настройка путей к файлам
directory=`pwd`
work_directory=${directory%func_tests*}
data="/func_tests/data/"
test_in_file="$work_directory$data$in_file"
test_out_file="$work_directory$data$out_file"

#Очистка вывода программы и запуск опредённого режима
if [ $USE_VALGRIND -ne 0 ]; then
	programm="/app.exe"
	programm_file="$work_directory$programm"
	eval $programm_file < $test_in_file > current.txt
else
	programm="/a.out"
	programm_file="$work_directory$programm"
	val="valgrind "
	valgrind_file="$val$programm_file"
	echo \>\> $valgrind_file
	eval $valgrind_file < $test_in_file > current.txt
fi
eval sed -e 's/[^0-9.]//g' current.txt > out.txt
eval rm current.txt

#Запуск компоратора
com="/func_tests/scripts/comparator.sh"
comparator_file="$work_directory$com"
$comparator_file $test_out_file $number 0

#Удаление ненужного файла
eval rm out.txt
