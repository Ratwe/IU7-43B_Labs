#!/usr/bin/gnuplot -persist

all_files=system('ls ../prepdata/*')
O2_files=system('ls ../prepdata/*O2*')
O3_file="../prepdata/idx_O3.txt"

set terminal svg
set xlabel "Кол-во элементов, шт"
set ylabel "Время, мкс"
set grid


set key left top font ",8"
set datafile separator '|'


system('echo -n "\t\033[36mCREATING GRAPHS: 0/100%\033[0m \r"')

set title "Кусочно-линейный график"
set output "../graphs/linear.svg"
plot for [file in all_files] file title file[13:18] noenhanced with linespoints
system('echo -n "\t\033[36mCREATING GRAPHS: 33/100%\033[0m \r"')

set title "Кусочно-линейный график c ошибками, O2"
set output "../graphs/errors.svg"
plot for [file in O2_files] file using 1:2:4:5 title 'value-range-'.file[13:18] noenhanced with errorbars, \
     for [file in O2_files] file using 1:2 title file[13:18] noenhanced with lines
system('echo -n "\t\033[36mCREATING GRAPHS: 66/100%\033[0m \r"')

set title "Кусочно-линейный график с усами, O3"
set output "../graphs/mustache.svg"
plot O3_file using 1:6:5:4:7 title "Нижний и верхний квартиль" with candlesticks whiskerbars 0.5, \
     O3_file using 1:3:3:3:3 title "Средний квартиль" with candlesticks lt -1, \
     O3_file using 1:2 title O3_file[13:18] noenhanced with lines
system('echo -n "\t\033[36mCREATING GRAPHS: 100/100%\033[0m \r"')

system('echo "\t\033[32mCOMPLETE CREATING GRAPHS \033[0m"')
