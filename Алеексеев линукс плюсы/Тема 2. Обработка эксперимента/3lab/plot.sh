#! /usr/bin/gnuplot -persist
set terminal png enhanced
set output "plot.png"


#set xrange [0:10]


filename = 'plotting_data.txt'

plot filename using 1:2 title "target" with points #, \
#    filename using 3 title "linear regression" with lines, \
#    filename using 4 title "non-linear regression" with linespoints




