

export LD_LIBRARY_PATH=.


all: exe clear run


errors.o: errors.cpp errors.h
	g++ -c -fpic errors.cpp

opt.o: opt.cpp opt.h
	g++ -c -fpic opt.cpp

stats.o: stats.cpp stats.h
	g++ -c -fpic stats.cpp

complib: errors.o opt.o stats.o
	g++ -shared -Wl,-soname,libd2lab.so.1 -o libd2lab.so ./opt.o ./errors.o ./stats.o
	ldconfig -n .

exe: main.cpp complib
	g++ ./main.cpp -L. -ld2lab -o dynamic_2lab

plot: run
	gnuplot --persist  plot.sh

run: exe
	./dynamic_2lab >output.txt & 

clear:
	-rm *.o
