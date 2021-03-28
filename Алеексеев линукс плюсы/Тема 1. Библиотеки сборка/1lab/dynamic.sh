

if [ False ]
then

    # g++ -c -fpic dot.cpp
    # g++ -c -fpic gauss.cpp
    # g++ -c -fpic prog.cpp

    # # cоздаём файл библиотеки 
    # g++ -shared -Wl,-soname,libd1lab.so.1 -o libd1lab.so.1.0  ./dot.o ./gauss.o ./prog.o

    # mkdir dynamic_lib

    # cp libd1lab.so.1.0 ./dynamic_lib/libd1lab.so.1.0 

    # ldconfig -n ./dynamic_lib

    # # cоздадим файл libd1lab.so как мягкую ссылку
    # ln -s ./dynamic_lib/libd1lab.so.1.0 ./dynamic_lib/libd1lab.so


    # export LD_LIBRARY_PATH=./dynamic_lib

    # # compile
    # g++ ./test.cpp -L ./dynamic_lib -ld1lab -o dynamic_1lab
    echo "RUNNING"
fi



g++ -c -fpic dot.cpp
g++ -c -fpic gauss.cpp
g++ -c -fpic prog.cpp

# cоздаём файл библиотеки 
g++ -shared -Wl,-soname,libd1lab.so.1 -o libd1lab.so ./dot.o ./gauss.o ./prog.o

ldconfig -n .

export LD_LIBRARY_PATH=.

# compile
g++ ./test.cpp -L. -ld1lab -o dynamic_1lab

rm *.o

./dynamic_1lab >output.txt & 


