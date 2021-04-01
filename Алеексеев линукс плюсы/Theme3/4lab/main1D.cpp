#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>

#include "mult.h"

#define SIMULATIONS 1

using namespace std;

double rd()
{
    return rand() % 100;
}

void init_matrixes(int a_rows, int b_cols, int vec_len, double *&A, double *&B, double *&C)
{

    A = new double [a_rows*vec_len];
    B = new double [vec_len*b_cols];
    C = new double [a_rows*b_cols];

    for(int i=0;i<a_rows*vec_len;i++)
    A[i] = rd();
    for(int i=0;i<vec_len*b_cols;i++)
    B[i] = rd();
        for(int i=0;i<a_rows*b_cols;i++)
    C[i] = 0;
}

void delete_matrixes(int a_rows, int b_cols, int vec_len, double *&A, double *&B, double *&C)
{

    delete A, B, C;
}

void work(int type, int a_rows, int b_cols, int vec_len, double *&A, double *&B, double *&C)
{

    switch (type)
    {
    case 0:
        ijk2(A, B, a_rows, b_cols, vec_len, C);
        break;

    case 1:
        ikj2(A, B, a_rows, b_cols, vec_len, C);
        break;

    case 2:
        jik2(A, B, a_rows, b_cols, vec_len, C);
        break;

    case 3:
        jki2(A, B, a_rows, b_cols, vec_len, C);
        break;

    case 4:
        kij2(A, B, a_rows, b_cols, vec_len, C);
        break;

    case 5:
        kji2(A, B, a_rows, b_cols, vec_len, C);
        break;

    default:
        break;
    }
}

int main()
{

    double sum;
    int t1, t2, a_rows, b_cols, vec_len;

    vector<string> types = {"ijk", "ikj", "jik", "jki", "kij", "kji"};

    for (int s = 0; s<6;s++)
    {

        cout << "---> Type: " << types[s] << endl;

        for (auto v : {500, 1000, 2000})
        {

            a_rows = v;
            b_cols = v;
            vec_len = v;
            sum = 0;

            for (int i = 0; i < SIMULATIONS; i++)
            {
                double *A, *B, *C;
                init_matrixes(a_rows, b_cols, vec_len, A, B, C);
                t1 = clock();

                work(s, a_rows, b_cols, vec_len, A, B, C);

                t2 = clock();
                delete_matrixes(a_rows, b_cols, vec_len, A, B, C);

                sum += (double)(t2 - t1) / CLOCKS_PER_SEC;
            }
            std::cout << "size = " << v << "  time = " << sum / SIMULATIONS << endl;
        }
    }

    return 0;
}