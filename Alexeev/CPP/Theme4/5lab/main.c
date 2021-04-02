
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

    int item, size, i;
    int prod, p;

    MPI_Status st;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &item);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    prod = rand() % 15;
    printf("number from %d is %d\n", item, prod);
    

    if (item == 0)
    {
        for (i = 1; i < size; i++)
        {
            MPI_Recv(&p, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &st);
            prod *= p;
        }

        printf("Result is %d\n", prod);
    }
    else
    {
        MPI_Send(&prod, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
