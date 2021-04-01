
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define COUNT 1000

double integ(double (*f)(double), double a, double b, int count)
{

    double h = (b - a) / (count - 1);

    double sum = 0;
    for (int i = 1; i < count; i++)
        sum += f(a + i * h);

    return sum * h;
}

void MPIinteg(double (*f)(double), double a, double b, int count, MPI_Status st, double *result)
{

    int item, size, i;
    double sum = 0, s;

    MPI_Comm_rank(MPI_COMM_WORLD, &item);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double H = (b - a) / (size );

    sum = integ(f, a + H * item, a + H * (item + 1), count);
    printf("number from %d is %f\n", item, sum);

    if (item == 0)
    {
        for (i = 1; i < size; i++)
        {
            MPI_Recv(&s, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &st);
            sum += s;
        }

        printf("Result is %f from thread %d\n", sum, item);

        *result = sum;
    }
    else
    {
        MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    
}

double f(double x)
{
    return 8.0 / (3 * x + 4) / (3 * x + 4);
}
double g(double x)
{
    return 1.0 / (4 + x * x);
}

int main(int argc, char *argv[])
{

    double f_, g_;

    MPI_Status st;

    MPI_Init(&argc, &argv);

    MPIinteg(f, 0, 1, COUNT, st, &f_);
    MPIinteg(g, 0, 2, COUNT,  st, &g_);

    
    MPI_Finalize();

    printf("f - g = %f - %g = %f\n",f_, g_ , f_ - g_);




    return 0;
}
