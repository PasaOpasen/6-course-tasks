#include <vector>
#include <functional>

using namespace std;


class Polynom
{
private:

public:
    vector<double> coef;
    int degree;
    
    Polynom();
    Polynom(int deg);
    Polynom(double x);
    Polynom(vector<double> vec);
    Polynom(double coef, vector<double> roots);

    double Value(double value);

    friend Polynom operator+( Polynom a,  Polynom b);
    Polynom operator+=(Polynom a);
    friend Polynom operator+(Polynom a, double number);
    friend Polynom operator*( Polynom a,  Polynom b);
    friend Polynom operator*( double number,  Polynom b);
    friend Polynom operator/(Polynom a, double number);

    static Polynom Lagrange(vector<double> x, vector<double> y);
    static Polynom Newton(vector<double> x, vector<double> y);
    static Polynom Canon(vector<double> x, vector<double> y);

    static std::function<double(double)> Linear(vector<double> x, vector<double> y);
    static std::function<double(double)> Spline(vector<double> x, vector<double> y);

};



