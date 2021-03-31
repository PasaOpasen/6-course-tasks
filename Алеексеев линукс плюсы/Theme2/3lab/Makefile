

export LD_LIBRARY_PATH=.

gauss_path=../../Theme1/1lab

all: exe clear run

copylibs:
	echo "copy Gauss method library"
	cp ${gauss_path}/gauss.h ./gauss.h
	cp ${gauss_path}/prog.h ./prog.h
	cp ${gauss_path}/libd1lab.so ./libd1lab.so
	cp ${gauss_path}/libd1lab.so.1 ./libd1lab.so.1	


polynom.o: polynom.cpp polynom.h 
	g++ -c -fpic polynom.cpp 

complib: polynom.o
	g++ -shared -Wl,-soname,libd3lab.so.1 -o libd3lab.so ./polynom.o
	ldconfig -n .

exe: main.cpp complib copylibs
	g++ ./main.cpp -L.  -ld3lab -ld1lab -o dynamic_3lab

plot: run
	gnuplot --persist  plot.sh

run: exe
	./dynamic_3lab >output.txt 2>error.txt &

clear:
	-rm *.o