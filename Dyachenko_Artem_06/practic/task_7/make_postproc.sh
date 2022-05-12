#! /usr/bin/gnuplot -persist

print "Starting postprocessing..."

set terminal pdf

set xlabel "Кол-во элементов массива"
set ylabel "Время, мс"
set datafile separator ':'
set xtics 1000
set mxtics 2
set grid
set key left top font ",10"

set title "График зависимости времени выполнения от числа элементов массива"
list1 = system('ls method*')
set output "graph1.pdf"
plot for [file in list1] file title file noenhanced with linespoints


set title "График с ошибкой (O2, все методы)"
list2 = system('ls method*2')
set output "graph2.pdf"
plot for [file in list2] file using 1:2:4:5 title 'error '.file noenhanced with errorbars, \
     for [file in list2] file using 1:2 title file noenhanced with lines


set title "График с усами (О3, метод с квадратными скобками)"
set key right bot
file = "method_1_O3"
set output "graph3.pdf"
plot file using 1:4:5:6:7 title "Мин. и макс. значение;\nнижний и верхний квартиль\n" with candlesticks whiskerbars, \
    file using 1:3:3:3:3 title "Медиана" with candlesticks lt -1, \
    file using 1:2 title file noenhanced with lines

print "Postprocessing complete: graph1.pdf, graph2.pdf, graph3.pdf were created!\n"
