
#include <iostream>
#include <vector>
#include<iomanip>

using namespace std;


double square(double v){
    return v*v;
}

vector<double> mat_vector_dot(vector<vector<double>> mat, vector<double> vec)
{
    vector<double> answer(vec.size());

    for(int i = 0; i < vec.size(); i++){
        
        double sum(0);

        for(int j = 0; j < vec.size(); j++) sum += mat[i][j]*vec[j];

        answer[i] = sum;
    }
    
    // cout << "product vector:\n";
    // for(int i =0; i<vec.size(); i++) cout << setw(8) << setprecision(4) << answer[i];
    // cout << endl;

    return answer;

} 


double get_mse(vector<vector<double>> mat, vector<double> x, vector<double> y)
{
    auto product = mat_vector_dot(mat, x);

    double sum(0);

    for(int i = 0;i < x.size(); i++) sum += square(product[i]-y[i]);

    return sum/x.size();

}

