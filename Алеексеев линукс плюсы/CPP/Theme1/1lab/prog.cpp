#include <vector>

using namespace std;

vector<double> Prog(vector<vector<double>> A, vector<double> vec)
{

    int n = vec.size();

    vector<double> a(n+1), b(n+1), c(n+1), alp(n+1), bet(n+1), x(n);

    //Заполнение массивов диагоналей
    b[1] = A[1 - 1][1 - 1];
    c[1] = A[1 - 1][2 - 1];
    for (int i = 2; i < n; i++)
    {
        b[i] = A[i - 1][i - 1];
        c[i] = A[i - 1][i + 1 - 1];
        a[i] = A[i - 1][i - 1 - 1];
    }
    b[n] = A[n - 1][n - 1];
    a[n] = A[n - 1][n - 1 - 1];


    //прямой ход
    alp[2] = -c[1] / b[1];
    bet[2] = vec[1 - 1] / b[1];
    for (int i = 2; i < n; i++)
    {
        double val = b[i] + a[i] * alp[i];
        alp[i + 1] = -c[i] / val;
        bet[i + 1] = (-a[i] * bet[i] + vec[i - 1]) / val;
    }

    //обратный ход
    x[n - 1] = (-a[n] * bet[n] + vec[n - 1]) / (b[n] + a[n] * alp[n]);
    for (int i = n - 1; i >= 1; i--)
    {
        x[i - 1] = alp[i + 1] * x[i + 1 - 1] + bet[i + 1];
    }



    return x;
}