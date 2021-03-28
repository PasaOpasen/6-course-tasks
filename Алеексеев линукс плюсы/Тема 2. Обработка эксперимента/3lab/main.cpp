#include <vector>
#include <functional>
#include <iostream>
#include <fstream>

using namespace std;



int main(){


vector<double> x = {0.68,0.73,0.80,0.88,0.93,0.99};
vector<double> y = {0.80866,0.89492,1.02964,1.20966,1.34087,1.52368};

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


    return 0;
}