


g++ -c dot.cpp
g++ -c gauss.cpp
g++ -c prog.cpp

ar crs lib1lab.a ./dot.o ./gauss.o ./prog.o

g++ test.cpp -L. -l1lab -o 1lab

rm *.o

./1lab >output.txt & 