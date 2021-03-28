
#include <iostream>

#include "dot.h"
#include "gauss.h"
#include "prog.h"

using namespace std;


void test_Gauss(vector<vector<double>> matrix, vector<double> vector)
{

    auto solution = Gauss(matrix, vector);
    cout << "Error with Gauss: " << get_mse(matrix, solution, vector) << endl;
}

void test_Pro(vector<vector<double>> matrix, vector<double> vector)
{

    auto solution = Prog(matrix, vector);
    cout << "\n\nError with ProRace: " << get_mse(matrix, solution, vector) << endl;
}


struct SLAU
{
    vector<vector<double>> A;
    vector<double> y;

    SLAU(vector<vector<double>> A_, vector<double> y_)
    {
        A = A_;
        y = y_;
    }
};


SLAU ex1 = SLAU(
{ 
    { 1, 1},
    { 2, 3} 
},

{1,3}

);

SLAU ex2 = SLAU(
{ 
    { -1, 1, 1 },
    { 56, -2, 23 },
    { 31, 0.4, 1} 
},

{-1, 9, 3}

);




SLAU ex3 = SLAU(
{ 
    { -1, 1, 1 },
    { 1, -2, 2.3 },
    { 11, 0.46, 1} 
},

{-10, 9, 3}

);



SLAU ex4 = SLAU(
{ 
    { -1, 1, 1 , 0, 5},
    { 1, -2, 2.3 , 12, 11},
    { 11, 0.46, 1, -5, -3},
    { 1, 0.46, 1, -5, -3},
    { 6, 0.5, 3, -2, -7}         
},

{-10, 9, 3, 14, -145}

);




SLAU ex5 = SLAU(
{ 
    { -1, 1, 0 , 0, 0},
    { 1, -2, 2.3 , 0, 0},
    { 0, 0.46, 1, -5, 0},
    { 0, 0, 1, -5, -3},
    { 0, 0, 0, -2, -7}         
},

{-10, 9, 3, 14, -145}

);

SLAU ex6 = SLAU(
{ 
    { -1, 1, 0 , 0, 0},
    { 1, -200, 2.3 , 0, 0},
    { 0, 0.49086, 1, -5, 0},
    { 0, 0, 1, -0.75, -3},
    { 0, 0, 0, -2, -76}         
},

{-10, 2, 30, 14, -145}

);






int main()
{
    test_Gauss(ex1.A, ex1.y);
    test_Gauss(ex2.A, ex2.y);
    test_Gauss(ex3.A, ex3.y);
    test_Gauss(ex4.A, ex4.y);

    cout << "\n\n\n";

    //test_Gauss(ex5.A, ex5.y);
    test_Pro(ex5.A, ex5.y);
    test_Pro(ex6.A, ex6.y);

    return 0;
}
