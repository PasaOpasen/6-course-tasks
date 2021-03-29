#include <vector>
#include <functional>

using namespace std;


class Polynom
{
private:
    vector<double> coef;
    int degree;
public:
    Polynom(int deg);
    Polynom(vector<double> vec);

    double Value(double value);

    Polynom Lagrange(vector<double> x, vector<double> y);
    Polynom Newton(vector<double> x, vector<double> y);
    Polynom Canon(vector<double> x, vector<double> y);

    std::function<double(double)> Linear();
    std::function<double(double)> Spline();

};



