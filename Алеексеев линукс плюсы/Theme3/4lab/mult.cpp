

using namespace std;

void ijk(double **A, double **B, int a_rows, int b_cols, int vec_len, double **C)
{

    int i, j, k;

    for (i = 0; i < a_rows; i++)
        for (j = 0; j < b_cols; j++)
            for (k = 0; k < vec_len; k++)
                C[i][j] += A[i][k] * B[k][j];
}
