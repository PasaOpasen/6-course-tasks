
//#include <cstdlib>

//double rd()
//{
//    return rand() % 100;
//}

#include <iostream>
#include <cstdio>
#include <ctime>

#define SIMULATIONS 30

using namespace std;


void init_matrixes(int a_rows, int b_cols, int vec_len, double **A, double **B, double **C)
{

    A = new double *[a_rows];
    B = new double *[vec_len];
    C = new double *[a_rows];

    for (int i = 0; i < a_rows; i++)
    {
        A[i] = new double[vec_len];
        C[i] = new double[b_cols];
    }
    for (int i = 0; i < vec_len; i++)
        B[i] = new double[b_cols];
}

int main()
{

    double s;
    int t1, t2;
    double **A, **B, **C;

    for (int i = 0; i < SIMULATIONS; i++)
    {
        init_matrixes(1, 1, 1, A, B, C);
        t1 = clock();

        t2 = clock();

        s += (double)(t2 - t1) / CLOCKS_PER_SEC;
    }
    cout << s / SIMULATIONS << endl;

    return 0;
}