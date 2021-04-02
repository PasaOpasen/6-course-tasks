
#include <vector>
#include <cmath>

using namespace std;

double MAE(vector<double> v1, vector<double> v2)
{

    double sum = 0;
    for (int i = 0; i < v1.size(); i++)
        sum += fabs(v1[i] - v2[i]);

    return sum/v1.size();
}


double square(double a){
    return a*a;
}

double MSE(vector<double> v1, vector<double> v2)
{

    double sum = 0;
    for (int i = 0; i < v1.size(); i++)
        sum += square(v1[i] - v2[i]);

    return sum/v1.size();
}
