#include <vector>
#include <functional>

using namespace std;


class Polynom
{
private:

public:
    vector<double> coef;
    int degree;
    
    Polynom(int deg);
    Polynom(vector<double> vec);
    Polynom(double coef, vector<double> roots);

    double Value(double value);

    static vector<double> Sum( Polynom& a,  Polynom& b);

    static Polynom Lagrange(vector<double> x, vector<double> y);
    static Polynom Newton(vector<double> x, vector<double> y);
    static Polynom Canon(vector<double> x, vector<double> y);

    static std::function<double(double)> Linear();
    static std::function<double(double)> Spline();

};



