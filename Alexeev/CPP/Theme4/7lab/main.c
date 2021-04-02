
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

// при сильном увеличении программа умирает из-за ошибки сегментации
#define AROWS 4
#define CROWS 4
#define CCOLS 6

int rd() // как я понял, в нативном С (и С++) нет генератора действительных случайных чисел, только целые либо подключай страшные библиотеки с шаблонами и чем-то таким
{
    return rand() % 15;
}

int main(int argc, char *argv[])
{

    // заполнение матриц случайными числами и нулями

    double A[AROWS][CROWS], B[AROWS][CROWS], C[CROWS][CCOLS], F[AROWS][CCOLS], F2[AROWS][CCOLS];

    for (int i = 0; i < AROWS; i++)
    {
        for (int j = 0; j < CROWS; j++)
        {
            A[i][j] = rd();
            B[i][j] = rd();
        }

        for (int j = 0; j < CCOLS; j++)
            F[i][j] = 0.; // вообще-то это итоговая матрица, ее заполнять не надо, но лучше заполнить нулями для красивого вида потом
    }
    for (int i = 0; i < CROWS; i++)
    {
        for (int j = 0; j < CCOLS; j++)
            C[i][j] = rd();
    }

    int item, size, i, j;
    int total_elements = CCOLS * AROWS; // всего элементов в итоговой матрице

    MPI_Status st;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &item);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int counts[size];                       // сколько каждому потоку придется создать элементов (первым нескольким может понадобиться сделать на 1 больше)
    int ost = total_elements % size;        // остаток от деления на число потоков
    int un = (total_elements - ost) / size; // общая часть для всех потоков
    for (i = 0; i < size; i++)
        counts[i] = un;
    for (i = 0; i < ost; i++)
        counts[i] += 1;

    double buff0[counts[0]], buff1[counts[size - 1]]; // приходится сделать два буффера под разные размеры, указатели почему-то не работают у меня на С

    // каждый поток считает свои элементы в матрице по такому правилу: нумеруем элементы в ряд и относим потокам по типу (1 2 3 4 1 2 3 4 1 2 3)
    int counter = 0;
    for (int k = 0; k < CCOLS * AROWS; k++)
        if (k % size == item)
        {
            i = k % CCOLS;
            j = k - i * CCOLS;

            double AC = 0, BC = 0;

            for (int t = 0; t < CROWS; t++)
            {
                AC += A[i][t] * C[t][j]; // можно и короче записать, конечно
                BC += B[i][t] * C[t][j];
            }
            double sum = AC + BC;
            F[i][j] = sum;

            // тут идея в том, что в зависимости от потока буфер будет своего размера, а этот размер надо много где учитывать
            if (item < ost) // проверка показывает, какой размер буфера нужен этому потоку
                buff0[counter] = sum;
            else
                buff1[counter] = sum;
            counter++;
        }

    if (item == size - 1) // главный поток будет последним, потому что перед этим ему меньше делать (так как последний, на него не приходятся дополнительные элементы)
    {
        // делается разархивация для самого себя
        counter = 0;
        for (int k = 0; k < CCOLS * AROWS; k++)
            if (k % size == item)
            {
                i = k % CCOLS;
                j = k - i * CCOLS;

                // тут идея в том, что в зависимости от потока буфер будет своего размера, а этот размер надо много где учитывать
                if (item < ost)
                    F2[i][j] = buff0[counter];
                else
                    F2[i][j] = buff1[counter];
                counter++;
            }

        // и для других потоков
        for (int ii = 0; ii < size - 1; ii++)
        {
            if (item < ost) // вот зачем разные буфферы
                MPI_Recv(buff0, counts[ii], MPI_DOUBLE, ii, 0, MPI_COMM_WORLD, &st);
            else
                MPI_Recv(buff1, counts[ii], MPI_DOUBLE, ii, 0, MPI_COMM_WORLD, &st);

            counter = 0;
            for (int k = 0; k < CCOLS * AROWS; k++)
                if (k % size == ii)
                {
                    i = k % CCOLS;
                    j = k - i * CCOLS;

                    if (item < ost)
                        F2[i][j] = buff0[counter];
                    else
                        F2[i][j] = buff1[counter];
                    counter++;
                }
        }
    }
    else
    {
        if (item < ost)
            MPI_Send(buff0, counts[item], MPI_DOUBLE, size - 1, 0, MPI_COMM_WORLD);
        else
            MPI_Send(buff1, counts[item], MPI_DOUBLE, size - 1, 0, MPI_COMM_WORLD);
    }

    // после следующего кода (может быть, не с первой попытки)
    // будут выведены матрицы F от каждого потока
    // и матрица F2, которая является объединением работы всех потоков
    // не получилось так легко завернуть вывод матриц в функцию, потому что нельзя создавать функцию с аргументами типа [][], не указывая размер измерений заранее

    printf("\n");
    for (int i = 0; i < AROWS; i++)
    {
        printf("||\t");
        for (int j = 0; j < CCOLS; j++)
        {
            printf("%.0f\t", F[i][j]);
        }
        printf("||\n");
    }

    if (item == size - 1)
    {
        printf("\n TOTAL \n");
        for (int i = 0; i < AROWS; i++)
        {
            printf("||\t");
            for (int j = 0; j < CCOLS; j++)
            {
                printf("%.0f\t", F2[i][j]);
            }
            printf("||\n");
        }
    }

    MPI_Finalize();
    return 0;
}
