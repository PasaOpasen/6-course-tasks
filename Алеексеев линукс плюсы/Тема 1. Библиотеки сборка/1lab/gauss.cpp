
#include <iostream>
#include <vector>
//#include <stdexcept>
#include <iomanip>

using namespace std;

vector<vector<double>> LinesSwap(vector<vector<double>> A, int n1, int n2){
    
    vector<double> t = A[n1];
    A[n1] = A[n2];
    A[n2] = t;
    return A;
}

vector<vector<double>> LinesDiff(vector<vector<double>> A, int n1, int n2, double coef){
    
    for(int i=0; i<A[0].size();i++)
        A[n1][i] -= coef * A[n2][i];

    return A;
}





vector<double> Gauss(vector<vector<double>> matrix, vector<double> vector)
{

    int size = vector.size();

    std::vector<std::vector<double>> S(size, std::vector<double>(size + 1));
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
            S[i][j] = matrix[i][j];
        S[j][size] = vector[j];
    }

    //S.LinesDiff(2, 1, 2); S.PrintMatrix();

    for (int j = 0; j < size; j++)
    {
        int k = j;
        if (S[k][j] == 0) //если ведущий элемент равен нулю, поменять эту строку местами с ненулевой
        {
            int h = k;
            while (S[h][j] == 0)
                h++;
            S = LinesSwap(S, k, h);
        }

        while (S[k][j] == 0 && k < size - 1)
            k++; //найти ненулевой элемент
        int l = k + 1;
        if (k != size - 1)
            while (l != size)
            {
                S = LinesDiff(S, l, k, S[l][j] / S[k][j]);
                l++;
            } //отнимать от строк снизу
              //S.PrintMatrix();Console.WriteLine();
        l = k - 1;
        if (k != 0)
            while (l != -1)
            {
                S = LinesDiff(S, l, k, S[l][j] /S[k][j]);
                l--;
            } //отнимать от строк сверху
    }

    cout << "\n ---------------------------------\n";
    cout << "Result  matrix is:\n";

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size + 1; j++)
            cout << setw(8) << setprecision(4) << S[i][j];
        cout << endl;
    }


    std::vector<double> x(size);
    for (int i = 0; i < size; i++)
        x[i] = S[i][size] / S[i][i];


    return x;

    // double coef;

    // //variables for loops
    // int i, j, k;

    // int N = vector.size();

    // if (N != matrix.size() || N != matrix[0].size())
    //     throw std::invalid_argument("not equal dimensions");

    // for (j = 0; j < N; j++)
    // {

    //     if (matrix[j][j] != 0)

    //         for (i = 0; i < N; i++)
    //             if (i != j)
    //             {
    //                 coef = matrix[i][j] / matrix[j][j];

    //                 for (k = 0; k < N; k++)
    //                     matrix[i][k] -= matrix[j][k] * coef;

    //                 vector[i] -= vector[j] * coef;
    //             }
    // }

    // //print the Diagonal matrix

    // cout << "\n ---------------------------------\n";
    // cout << "\n Diagonal  Matrix is:\n";

    // for (i = 0; i < N; i++)
    // {
    //     for (j = 0; j < N; j++)
    //         cout << setw(8) << setprecision(4) << matrix[i][j];
    //     cout << endl;
    // }

    // // cout << "\n ---------------------------------\n";

    // //print values of x,y,z

    // cout << "\n\n The Solution is:\n";
    // for (i = 0; i < N; i++)
    // {
    //     vector[i] /= matrix[i][i];
    //     cout << "x[" << setw(3) << i + 1 << "]=" << setw(7) << setprecision(4) << vector[i] / matrix[i][i] << endl;
    // }

    // cout << "\n \n";

    // return vector;
}
