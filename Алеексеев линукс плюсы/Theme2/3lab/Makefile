

export LD_LIBRARY_PATH=.


all: exe clear run

copylibs:
	cp cd ../../

gauss

polynom.o: polynom.cpp polynom.h
	g++ -c -fpic polynom.cpp

complib: polynom.o
	g++ -shared -Wl,-soname,libd3lab.so.1 -o libd3lab.so ./polynom.o
	ldconfig -n .

exe: main.cpp complib
	g++ ./main.cpp -L. -ld3lab -o dynamic_3lab

plot: run
	gnuplot --persist  plot.sh

run: exe
	./dynamic_3lab >output.txt & 

clear:
	-rm *.o