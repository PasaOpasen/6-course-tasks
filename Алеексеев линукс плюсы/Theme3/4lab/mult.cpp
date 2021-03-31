
#include "mult.h"

using namespace std;

void ijk(double **&A, double **&B, int a_rows, int b_cols, int vec_len, double **&C)
{

    int i, j, k;

    for (i = 0; i < a_rows; i++)
        for (j = 0; j < b_cols; j++)
            for (k = 0; k < vec_len; k++)
                C[i][j] += A[i][k] * B[k][j];
}

void ikj(double **&A, double **&B, int a_rows, int b_cols, int vec_len, double **&C)
{

    int i, j, k;

    for (i = 0; i < a_rows; i++)
        for (k = 0; k < vec_len; k++)
            for (j = 0; j < b_cols; j++)
                C[i][j] += A[i][k] * B[k][j];
}
void jik(double **&A, double **&B, int a_rows, int b_cols, int vec_len, double **&C)
{

    int i, j, k;

    for (j = 0; j < b_cols; j++)
        for (i = 0; i < a_rows; i++)
            for (k = 0; k < vec_len; k++)
                C[i][j] += A[i][k] * B[k][j];
}

void jki(double **&A, double **&B, int a_rows, int b_cols, int vec_len, double **&C)
{

    int i, j, k;

    for (j = 0; j < b_cols; j++)
        for (k = 0; k < vec_len; k++)
            for (i = 0; i < a_rows; i++)
                C[i][j] += A[i][k] * B[k][j];
}

void kij(double **&A, double **&B, int a_rows, int b_cols, int vec_len, double **&C)
{

    int i, j, k;

    for (k = 0; k < vec_len; k++)
        for (i = 0; i < a_rows; i++)
            for (j = 0; j < b_cols; j++)

                C[i][j] += A[i][k] * B[k][j];
}

void kji(double **&A, double **&B, int a_rows, int b_cols, int vec_len, double **&C)
{

    int i, j, k;

    for (j = 0; j < b_cols; j++)
        for (k = 0; k < vec_len; k++)
            for (i = 0; i < a_rows; i++)
                C[i][j] += A[i][k] * B[k][j];
}

///


void ijk2(double *&A, double *&B, int a_rows, int b_cols, int vec_len, double *&C)
{

    int i, j, k;

    for (i = 0; i < a_rows; i++)
        for (j = 0; j < b_cols; j++)
            for (k = 0; k < vec_len; k++)
                C[i * b_cols + j] += A[i * vec_len + k] * B[k  * b_cols + j];
}

void ikj2(double *&A, double *&B, int a_rows, int b_cols, int vec_len, double *&C)
{

    int i, j, k;

    for (i = 0; i < a_rows; i++)
        for (k = 0; k < vec_len; k++)
            for (j = 0; j < b_cols; j++)
                C[i * b_cols + j] += A[i * vec_len + k] * B[k  * b_cols + j];
}
void jik2(double *&A, double *&B, int a_rows, int b_cols, int vec_len, double *&C)
{

    int i, j, k;

    for (j = 0; j < b_cols; j++)
        for (i = 0; i < a_rows; i++)
            for (k = 0; k < vec_len; k++)
                C[i * b_cols + j] += A[i * vec_len + k] * B[k  * b_cols + j];
}

void jki2(double *&A, double *&B, int a_rows, int b_cols, int vec_len, double *&C)
{

    int i, j, k;

    for (j = 0; j < b_cols; j++)
        for (k = 0; k < vec_len; k++)
            for (i = 0; i < a_rows; i++)
                C[i * b_cols + j] += A[i * vec_len + k] * B[k  * b_cols + j];
}

void kij2(double *&A, double *&B, int a_rows, int b_cols, int vec_len, double *&C)
{

    int i, j, k;

    for (k = 0; k < vec_len; k++)
        for (i = 0; i < a_rows; i++)
            for (j = 0; j < b_cols; j++)

                C[i * b_cols + j] += A[i * vec_len + k] * B[k  * b_cols + j];
}

void kji2(double *&A, double *&B, int a_rows, int b_cols, int vec_len, double *&C)
{

    int i, j, k;

    for (j = 0; j < b_cols; j++)
        for (k = 0; k < vec_len; k++)
            for (i = 0; i < a_rows; i++)
                C[i * b_cols + j] += A[i * vec_len + k] * B[k  * b_cols + j];
}


