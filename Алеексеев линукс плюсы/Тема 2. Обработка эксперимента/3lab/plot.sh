#! /usr/bin/gnuplot -persist
set terminal png enhanced
set output "plot.png"


#set xrange [0:10]


filename = 'plotting_data.txt'
file2 = 'polynom.txt'

plot file2 using 1:2 title "Lagrange" with lines , \
    file2 using 1:3 title "Newton"   # , \
#    filename using 1:2 title "target" with points 




