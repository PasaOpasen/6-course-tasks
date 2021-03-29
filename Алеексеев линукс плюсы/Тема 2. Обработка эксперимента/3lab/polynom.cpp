
#include <vector>
#include <functional>
#include "polynom.h"

using namespace std;

Polynom::Polynom(int deg)
{
    this->degree = deg;

    vector<double> coef(deg + 1, 0);
    this->coef = coef;
}

Polynom::Polynom(vector<double> coef)
{
    this->degree = coef.size() - 1;
    this->coef = coef;
}

double Polynom::Value(double value)
{
    double sum = this->coef[this->degree];
    if (this->degree > 0)
    {
        for (int i = (this->degree - 1); i >= 0; i--)
        {
            sum *= value;
            sum += this->coef[i];
        }
    }

    return sum;
}

Polynom Polynom::Lagrange(vector<double> x, vector<double> y){
    
}
