#! /usr/bin/gnuplot -persist
set terminal pngcairo enhanced font "Times New Roman,12.0" size 35cm,31cm 
set output "plot.png"
set view 180,0,1.5

do for[p in '0.896 0.774 0.955']{

    set arrow from p, graph 0 to p, graph 1 nohead

}

#set xrange [0:10]


filename = 'plotting_data.txt'
file2 = 'polynom.txt'

plot file2 using 1:2 title "Lagrange" with lines lt -1, \
    file2 using 1:3 title "Newton" with points pointsize 1 pointtype 10 lt 1, \
    file2 using 1:4 title "Canonic"    , \
    file2 using 1:5 title "Linear"  with lines lt 6  , \
    file2 using 1:6 title "Spline" with linespoint pointsize 1 pointtype 4 lt 7




