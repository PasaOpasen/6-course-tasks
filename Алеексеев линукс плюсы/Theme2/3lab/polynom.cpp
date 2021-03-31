
#include <vector>
#include <functional>
#include <cmath>
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

// Задать полином по старшему коэффициенту и набору его корней
Polynom::Polynom(double coef, vector<double> roots)
{
    int size = roots.size();

    this->degree = size;
    vector<double> c(size + 1);
    this->coef = c;
    //коэффициенты для приведённого полинома первой степени
    this->coef[0] = -roots[0];
    this->coef[1] = 1;
    if (size > 1)
    { //вычисление коэффициентов полинома степени k
        //Console.WriteLine("{0}", this->coef[0]);
        for (int k = 2; k <= this->degree; k++)
        {
            this->coef[k] = this->coef[k - 1];
            for (int i = k - 1; i > 0; i--)
                this->coef[i] = this->coef[i - 1] - this->coef[i] * roots[k - 1];
            this->coef[0] *= -roots[k - 1];
        }
    }
    //умножение на старший коэффициент
    for (int i = 0; i <= this->degree; i++)
        this->coef[i] *= coef;
}

//меня с этих плюсов очень дико бомбило
// короче по логике здесь нужно возвращать полином, его легко создать и вернуть в самом конце, в других языках это так и делается
// но здесь возникает проблема с тем, что я передаю ссылку на локальную переменную, которая локальная и после вызова функции удаляется блабла
// почему именно эту ссылку нельзя сохранять -- не знаю
// попробовал вставлять const и т п, но ругается уже на static
// operator тоже не использовал, потому что ему опять что-то не нравится
vector<double> Polynom::Sum(Polynom &a, Polynom &b)
{
    int degree = max(a.degree, b.degree);
    
    vector<double> coef(degree + 1);


    for (int i = 0; i <= min(a.degree, b.degree); i++)
        coef[i] = a.coef[i] + b.coef[i];
    for (int i = min(a.degree, b.degree) + 1; i <= degree; i++)
    {
        if (a.degree > b.degree)
            coef[i] = a.coef[i];
        else
            coef[i] = b.coef[i];
    }
    //Polynom result(coef);

    return coef;
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

Polynom Polynom::Lagrange(vector<double> x, vector<double> y)
{
    int size = x.size();

    int degree = size - 1;

    Polynom PL(degree);           //конечный полином
    vector<double> roots(degree); //массив корней

    for (int k = 0; k <= degree; k++)
    { //задание корней полиномов Pk
        for (int i = 0; i < k; i++)
            roots[i] = x[i];
        for (int i = k + 1; i <= degree; i++)
            roots[i - 1] = x[i];

        Polynom c(1, roots); //приведённый полином

        double An = y[k] / c.Value(x[k]); //вычисление старшего коэффициента
        Polynom Pk(An, roots);            //создание полинома Pk
        PL = Polynom(Sum(PL, Pk));                 //прибавление к общему
    }
    return PL;
}

double W(vector<double> &x, vector<double> &y, int i, int j)
{
    if (j - i == 1)
        return (y[j] - y[i]) / (x[j] - x[i]);
    return (W(x, y, i + 1, j) - W(x, y, i, j - 1)) / (x[j] - x[i]);
}

Polynom Polynom::Newton(vector<double> x, vector<double> y)
{
    int size = x.size();
    vector<double> coef(1, y[0]);

    Polynom pol(coef); //Первый элемент суммы полиномов
                       //np = new Polynom[P.Length];

    vector<double> *mas = new vector<double>[size];
    for (int i = 0; i < size; i++)
    {
        vector<double> v(i + 1);
        mas[i] = v;
        for (int j = 0; j <= i; j++)
            mas[i][j] = x[j]; //Заполнить массив массивов корней
    }
    for (int i = 0; i < size - 1; i++)
    {
        Polynom newpol(W(x, y, 0, i + 1), mas[i]);

        pol = Polynom(Sum(pol, newpol)); //Просуммировать полиномы
                                //np[i] = new Polynom(pol);
    }

    return pol;
}







std::function<double(double)> Polynom::Linear(){

}
std::function<double(double)> Polynom::Spline(){
    
}
