#include <vector>
#include <functional>
#include <iostream>
#include <fstream>

#include "polynom.h"

#define N 20

using namespace std;

int main()
{

    vector<double> x = {0.68, 0.73, 0.80, 0.88, 0.93, 0.99};
    vector<double> y = {0.80866, 0.89492, 1.02964, 1.20966, 1.34087, 1.52368};

    vector<double> tg = {0.896, 0.774, 0.955};

    int size = x.size();

    ofstream file;
    file.open("plotting_data.txt");
    file << "x\ttarget" << endl;
    for (int i = 0; i < size; i++)
    {
        file << x[i] << "\t" << y[i];
        if (i != size - 1)
            file << endl;
    }

    file.close();



    auto lag = Polynom::Lagrange(x, y);
    auto newt = Polynom::Newton(x, y);
    auto canon = Polynom::Canon(x, y);
    auto lin = Polynom::Linear(x,y);
    auto spl = Polynom::Spline(x,y);

    double step = (x[x.size()-1] - x[0])/(N-1);

    vector<double> t(N), lg(N), nt(N), cn(N), ln(N), sp(N);
    for(int i=0;i<N;i++){
        t[i] = x[0] + i*step;

        lg[i] = lag.Value(t[i]);
        nt[i] = newt.Value(t[i]);
        cn[i] = canon.Value(t[i]);
        ln[i] = lin(t[i]);
        sp[i] = spl(t[i]);
    }

    file.open("polynom.txt");
    file << "x\tlag\tnewt\tcanon\tlin\tspl" << endl;
    for (int i = 0; i < N; i++)
    {
        file << t[i] << "\t" << lg[i] << "\t" << nt[i] << "\t" << cn[i]<< "\t" << ln[i] << "\t" << sp[i];
        if (i != N - 1)
            file << endl;
    }

    file.close();



    return 0;
}