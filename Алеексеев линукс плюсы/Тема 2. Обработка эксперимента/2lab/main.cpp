
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>

#include "opt.h"
#include "errors.h"
#include "stats.h"

using namespace std;

std::function<double(double)> eval_func(vector<double> input, vector<double> output, vector<double> start_params)
{

    // my lambda function with params
    auto f = [](double v, vector<double> params) {
        return params[0] / (params[1] * v + params[2]);
    };

    auto minized = [input, output, f](vector<double> params) {
        vector<double> result(input.size());
        for (int i = 0; i < input.size(); i++)
            result[i] = f(input[i], params);

        return MSE(result, output);
    };

    auto best_params = gradient_solve((std::function<double(vector<double>)>)minized, start_params, 0.01, 1000);

    // my lambda function with best params
    auto my_func = [best_params, f](double v) {
        return f(v, best_params);
    };

    return my_func;
}

int main()
{

    vector<double> input = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<double> output = {0.529, 0.298, 0.267, 0.171, 0.156, 0.124, 0.1, 0.078, 0.075};

    int size = input.size();

    auto my_func = eval_func(input, output, {1, 1, 1});
    auto regression = linear_regression(input, output);

    vector<double> out1(size), out2(size);
    for (int i = 0; i < size; i++)
    {
        out1[i] = my_func(input[i]);
        out2[i] = regression(input[i]);
    }

    cout << "MSE for linear regression = " << MSE(output, out2) << endl;
    cout << "MSE for non-linear regression = " << MSE(output, out1) << endl;

    ofstream file;
    file.open("plotting_data.txt");
    file << "x\ttarget\tlinear\tnonlinear\n";
    for (int i = 0; i < size; i++)
    {
        file << input[i] << "\t" << output[i] << "\t" << out2[i] << "\t" << out1[i];
        if (i != size - 1)
            file << endl;
    }

    file.close();

    return 0;
}
