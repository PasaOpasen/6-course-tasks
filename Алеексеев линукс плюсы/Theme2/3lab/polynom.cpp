
#include <vector>
#include <functional>
#include <cmath>
#include "polynom.h"
#include "gauss.h"
#include "prog.h"

using namespace std;

//constructors

Polynom::Polynom()
{
    this->degree = -1;
}

Polynom::Polynom(int deg)
{
    this->degree = deg;

    vector<double> coef(deg + 1, 0);
    this->coef = coef;
}

/// Приведённый одночлен по единственному корню (то есть 1(х-х0))
Polynom::Polynom(double x)
{
    this->degree = 1;
    this->coef = {-x, 1};
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

// operators

//меня с этих плюсов очень дико бомбило
// короче по логике здесь нужно возвращать полином, его легко создать и вернуть в самом конце, в других языках это так и делается
// но здесь возникает проблема с тем, что я передаю ссылку на локальную переменную, которая локальная и после вызова функции удаляется блабла
// почему именно эту ссылку нельзя сохранять -- не знаю
// попробовал вставлять const и т п, но ругается уже на static
// operator тоже не использовал, потому что ему опять что-то не нравится
Polynom operator+(Polynom a, Polynom b)
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

    return Polynom(coef);
}
Polynom Polynom::operator+=(Polynom a)
{
    return *this + a;
}

Polynom operator+(Polynom a, double number)
{
    auto c = a.coef;
    c[0] += number;
    return Polynom(c);
}

Polynom operator*(Polynom a, Polynom b)
{
    int degree = (a.degree + b.degree);
    vector<double> coef(degree + 1);
    for (int i = 0; i <= degree; i++)
    {
        double s = 0;
        for (int k = 0; k <= i; k++)
            if ((k <= a.degree) && ((i - k) <= b.degree))
                s += a.coef[k] * b.coef[i - k];
        coef[i] = s;
    }
    return Polynom(coef);
}

Polynom operator*(double number, Polynom b)
{
    auto t = b.coef;
    for (int i = 0; i < t.size(); i++)
        t[i] *= number;
    return Polynom(t);
}
Polynom operator/(Polynom a, double number)
{
    return (1.0 / number) * a;
}

// methods

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

        PL = PL + Polynom(An, roots);  //создание полинома Pk                       //прибавление к общему
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
                       //np = new Polynom[size];

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

        pol = pol + newpol; //Просуммировать полиномы
                       //np[i] = new Polynom(pol);
    }

    return pol;
}

Polynom Polynom::Canon(vector<double> x, vector<double> y)
{
    int size = x.size();

    vector<vector<double>> mat(size, vector<double>(size));

    for (int i = 0; i < size; i++)
    {
        mat[i][0] = 1;
        for (int j = 1; j < size; j++)
        {
            mat[i][j] = mat[i][j - 1] * x[i];
        }
    }

    vector<double> coef = Gauss(mat, y);

    Polynom pol(coef);

    return pol;
}

std::function<double(double)> Polynom::Linear(vector<double> x, vector<double> y)
{
    int size = x.size();

    Polynom *arr = new Polynom[size - 1];
    for (int i = 0; i < size - 1; i++)
        arr[i] = Polynom::Lagrange({x[i], x[i + 1]}, {y[i], y[i + 1]});

    //создание общей функции и вывод
    auto f = [x, size, arr](double v) {
        int n = size - 1; // polynom count

        if (v <= x[1])
            return arr[0].Value(v);
        if (v >= x[n])
            return arr[n-1].Value(v);

        int i1 = 1, i2 = n;
        //реализация бинарного поиска
        while (i2 - i1 != 1)
        {
            int tmp = (i1 + i2) / 2;
            if (v > x[tmp])
                i1 = tmp;
            else
                i2 = tmp;
        }

        return arr[i1].Value(v);
    };

    return f;
}

std::function<double(double)> Polynom::Spline(vector<double> x, vector<double> y)
{
    int size = x.size();

    double a_ = 0, b_ = 0;  //граничные условия (можно менять)
    bool is0outcut = false; // 0 out of bounds

    int n = size - 1; //записать в новую переменную для облегчения
    double *h = new double[n + 1];
    double *yy = new double[n + 1];


    for (int i = 1; i <= n; i++)
    {
        h[i] = x[i] - x[i - 1]; //Заполнение массива длин отрезков
        yy[i] = y[i] - y[i - 1];
    }

    //создание, заполнение и решение системы с трёхдиагональной матрицей

    vector<vector<double>> A(n + 1, vector<double>(n + 1));
    vector<double> b(n + 1);

    A[0][0] = -4.0 / h[1];
    A[0][1] = -2.0 / h[1];
    b[0] = -6.0 * yy[1] / (h[1] * h[1]) + a_;
    A[n][n - 1] = 2.0 / h[n];
    A[n][n] = 4.0 / h[n];
    b[n] = 6.0 * yy[n] / (h[n] * h[n]) + b_;
    for (int i = 1; i <= n - 1; i++)
    {
        A[i][i - 1] = 1.0 / h[i];
        A[i][i] = 2 * (1.0 / h[i] + 1.0 / h[i + 1]);
        A[i][i + 1] = 1.0 / h[i + 1];
        b[i] = 3 * (yy[i] / h[i] / h[i] + yy[i + 1] / h[i + 1] / h[i + 1]);
    }

    auto xx = Prog(A, b);

    //создание и заполнение массива полиномов
    Polynom *mas = new Polynom[n + 1];
    for (int i = 1; i <= n; i++)
    {
        Polynom p1, p2, p3, p4;
        
        p1 = Polynom(1, {x[i], x[i]}) * (2.0 * Polynom(x[i - 1]) + h[i]) / pow(h[i], 3) * y[i - 1];
        p2 = Polynom(1, {x[i - 1], x[i - 1]}) * (-2.0 * Polynom(x[i]) + h[i]) / pow(h[i], 3) * y[i];
        p3 = Polynom(1, {x[i], x[i]}) * Polynom(x[i - 1]) / pow(h[i], 2) * xx[i - 1];
        p4 = Polynom(1, {x[i - 1], x[i - 1]}) * Polynom(x[i]) / pow(h[i], 2) * xx[i];

        mas[i] = p1 + p2 + p3 + p4;
    }
    //mas[0] = mas[1];mas[n + 1] = mas[n];

    //создание общей функции и вывод
    auto f = [is0outcut, x, n, mas](double v) {
        if (v <= x[1])
            return (is0outcut) ? 0 : mas[1].Value(v);
        if (v >= x[n])
            return (is0outcut) ? 0 : mas[n].Value(v);

        int i1 = 1, i2 = n;
        //реализация бинарного поиска
        while (i2 - i1 != 1)
        {
            int tmp = (i1 + i2) / 2;
            if (v > x[tmp])
                i1 = tmp;
            else
                i2 = tmp;
        }

        return mas[i2].Value(v);
    };

    return f;
}
