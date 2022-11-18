#!/usr/bin/gnuplot -persist

set terminal pdf
set xlabel "Кол-во элементов, шт"
set ylabel "Время, мкс"
set grid
set key left top font ",7"
set datafile separator '|'

set title "Кусочно-линейный график\nОбычный способ перемножения матриц\nОптимизация Os"
set output "../graphics/main_Os.pdf"
plot "../prepdata/main_Os.txt" title "main_Os" noenhanced with linespoints

set title "Кусочно-линейный график\nОбычный способ перемножения матриц\nОптимизация O0"
set output "../graphics/main_O0.pdf"
plot "../prepdata/main_O0.txt" title "main_O0" noenhanced with linespoints

set title "Кусочно-линейный график\nОбычный способ перемножения матриц\nОптимизация O1"
set output "../graphics/main_O1.pdf"
plot "../prepdata/main_O1.txt" title "main_O1" noenhanced with linespoints

set title "Кусочно-линейный график\nОбычный способ перемножения матриц\nОптимизация O2"
set output "../graphics/main_O2.pdf"
plot "../prepdata/main_O2.txt" title "main_O2" noenhanced with linespoints

set title "Кусочно-линейный график\nОбычный способ перемножения матриц\nОптимизация O3"
set output "../graphics/main_O3.pdf"
plot "../prepdata/main_O3.txt" title "main_O3" noenhanced with linespoints

set title "Кусочно-линейный график\nCпособ перемножения матриц через транспонирования второй\nОптимизация Os"
set output "../graphics/transp_main_Os.pdf"
plot "../prepdata/transp_main_Os.txt" title "transp_main_Os" noenhanced with linespoints

set title "Кусочно-линейный график\nCпособ перемножения матриц через транспонирования второй\nОптимизация O0"
set output "../graphics/transp_main_O0.pdf"
plot "../prepdata/transp_main_O0.txt" title "transp_main_O0" noenhanced with linespoints

set title "Кусочно-линейный график\nCпособ перемножения матриц через транспонирования второй\nОптимизация O1"
set output "../graphics/transp_main_O1.pdf"
plot "../prepdata/transp_main_O1.txt" title "transp_main_O1" noenhanced with linespoints

set title "Кусочно-линейный график\nCпособ перемножения матриц через транспонирования второй\nОптимизация O2"
set output "../graphics/transp_main_O2.pdf"
plot "../prepdata/transp_main_O2.txt" title "transp_main_O2" noenhanced with linespoints

set title "Кусочно-линейный график\nCпособ перемножения матриц через транспонирования второй\nОптимизация O3"
set output "../graphics/transp_main_O3.pdf"
plot "../prepdata/transp_main_O3.txt" title "transp_main_O3" noenhanced with linespoints