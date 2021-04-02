#include <vector>
#include <functional>
#include <iostream>

using namespace std;

std::function<double(double)> linear_regression(vector<double> x, vector<double> y)
{

    double sumx(0), sumy(0), sumx2(0), sumxy(0);

    int n = x.size();

    for (int i = 0; i < n; i++)
    {
        sumx += x[i];
        sumy += y[i];
        sumx2 += x[i] * x[i];
        sumxy += x[i] * y[i];
    }

    double b = (n * sumxy - sumx * sumy) / (n * sumx2 - sumx * sumx);
    double a = (sumy - b * sumx) / n;

    cout << "\n\nCorrelation coef = " << b << "\n\n";

    auto f = [a, b](double v) {
        return a + v * b;
    };

    return f;
}