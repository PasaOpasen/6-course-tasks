

export LD_LIBRARY_PATH=.


all: exe clear run


dot.o: dot.cpp dot.h
	g++ -c -fpic dot.cpp

gauss.o: gauss.cpp gauss.h
	g++ -c -fpic gauss.cpp

prog.o: prog.cpp prog.h
	g++ -c -fpic prog.cpp

complib: dot.o gauss.o prog.o
	g++ -shared -Wl,-soname,libd1lab.so.1 -o libd1lab.so ./dot.o ./gauss.o ./prog.o
	ldconfig -n .

exe: test.cpp complib
	g++ ./test.cpp -L. -ld1lab -o dynamic_1lab


run: exe
	./dynamic_1lab >output.txt & 

clear:
	-rm *.o