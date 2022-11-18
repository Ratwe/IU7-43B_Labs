#! /usr/bin/gnuplot -persist

print "Starting postprocessing..."

set terminal pdf

system "mkdir -p graphs"

set xlabel "Кол-во строк в матрице"
set ylabel "Время, мс"
set datafile separator ':'
set xtics 10
set mxtics 2
set grid
set key left top font ",8"
set pointsize 0.4

set title "График зависимости времени выполнения от числа строк массива"
list1 = system('ls preproc/*')
set output "./graphs/graph1.pdf"
plot for [file in list1] file title file[9:] noenhanced with linespoints

print "Postprocessing complete: graph1.pdf was created!\n"
