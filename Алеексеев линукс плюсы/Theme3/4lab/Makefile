

export LD_LIBRARY_PATH=.


all: exe clear run


mult.o: mult.cpp mult.h 
	g++ -c -g -fpic mult.cpp 

complib: mult.o
	g++ -shared -Wl,-soname,libd4lab.so.1 -o libd4lab.so ./mult.o
	ldconfig -n .

exe: main.cpp complib
	g++ -g ./main.cpp -L.  -ld4lab -o dynamic_4lab
	g++ -g ./main1D.cpp -L.  -ld4lab -o dynamic_4lab1D


run: exe
	./dynamic_4lab >output.txt 2>error.txt &
	./dynamic_4lab1D >output1D.txt 2>error1D.txt &

clear:
	-rm *.o