// task1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <Windows.h>




template<typename T>
std::string array_to_string(T arr[], int len) 
{
    std::string res = "{";
    
    for(int i = 0; i < len; i++)
        res += " " + std::to_string(arr[i]);

    return res + " }";
}

void task1() {

    double arr[] = { 1.0, -3, -5, -6, 2, 1, 2, 56, 0, 90, -6.2, -7.2 };

    int index = -1;
    double max = 0;

    for (int i = 0; i < sizeof(arr) / sizeof(double); i++) {

        if (arr[i] < 0) {

            // можно написать круче, но мало кто поймет
            if (index < 0) {
                index = i;
                max = arr[i];
            }
            else if(arr[i] >= max) //>= чтобы брался последний возможный элемент
            {
                index = i;
                max = arr[i];
            }
        }
    }

    if (index < 0) {
        std::cout << "В массиве " << array_to_string(arr, sizeof(arr) / sizeof(double)) << " нет отрицательных чисел\n";
    }
    else {
        std::cout << "В массиве " << array_to_string(arr, sizeof(arr) / sizeof(double)) << " максимальный отрицательный элемент равен " << max << " и находится по индексу " << index<<"\n";
    }


}


void print_matrix(int *m, int rows, int cols) {
    for (int r = 0; r < rows; r++) 
    {
        std::cout << "|| ";
        for (int c = 0; c < cols; c++) 
        {
            std::cout << *((m + r * cols) + c) << " ";
        }
        std::cout << "||\n";
    }

}

void task2() {

    const unsigned int rows = 3, cols = 3;

    int matrix[rows][cols] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };


    int transposed[cols][rows];

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            transposed[c][r] = matrix[r][c];

    std::cout << "Start matrix: \n";
    print_matrix((int*)matrix, rows, cols);
    std::cout << "Transformed matrix: \n";
    print_matrix((int*)transposed, cols, rows);
}



void task3(int d1, int m1, int d2, int m2) {

    int days_by_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if(d1 < 1 || d2 < 1) std::cout << "День не может быть отрицательным\n";
    else if(m1<1 || m1 >12 || m2<1 || m2 > 12) std::cout << "Месяц должен быть в пределах 1-12\n";
    else if(d1 > days_by_month[m1-1] || d2 > days_by_month[m2 - 1]) std::cout << "День не может быть выше числа дней в месяце\n";
    else {

        int result = days_by_month[m1 - 1] - d1 + d2 - 1; 
        for (int m = m1+1; m < m2; m++)
            result += days_by_month[m - 1];

        std::cout << "Дней между датами: " << result << "\n";
    }


}


int main()
{
    SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода


    task1();
    std::cout << "\n";
    task2();
    std::cout << "\n";
    task3(15, 3, 25, 8);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
