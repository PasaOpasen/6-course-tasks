#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

long long nod(long long a, long long b) // Нахождение НОД по алгоритму Евклида.
{
	if (b == 0)
		return a;
	return nod(b, a % b);
}

long long mul(long long a, long long b, long long m) // При перемножении двух чисел типа long long может произойти переполнение типа еще до того, как мы возьмём результат по модулю. Поэтому используем функцию двоичного умножения двух чисел также по модулю.
{
	long long q = (long long)((long double)a * (long double)b / (long double)m);
	long long r = a * b - q * m;
	return (r + 5 * m) % m;
}

long long pows(long long a, long long b, long long m) // Быстрое возведение в степень по модулю.
{
	if (b == 0)
		return 1;
	if (b % 2 == 0)
	{
		long long t = pows(a, b / 2, m);
		return mul(t, t, m) % m;
	}
	return (mul(pows(a, b - 1, m), a, m)) % m;
}

bool Ferma(long long x) //Тест Ферма.
{
	if (x == 2)
		return true;
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		long long a = (rand() % (x - 2)) + 2;
		if (nod(a, x) != 1)
			return false;
		if (pows(a, x - 1, x) != 1)
			return false;
	}
	return true;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	ofstream fout1("Числа удовлетворяющие гипотезе.txt");
	ofstream fout2("Количество простых и составных чисел.txt");
	unsigned int n, cp = 0, cs = 0;
	cout << "Введите n: ";
	cin >> n;
	//n = 1000000;
	unsigned int *a = new unsigned int[n + 1]; // Формируем массив простых чисел откуда будем брать числа для проверки гипотезы.
	//Решето Эратосфена---------------------------------------
	for (unsigned int i = 0; i < n + 1; i++)
	{
		a[i] = i;
	}
	for (unsigned int p = 2; p < n + 1; p++)
	{
		if (a[p] != 0)
		{
			if (a[p] <= 500000000)
			{
				a[p] = 0;
			}
			//			else // Для отладки: вывод всех простых чисел
			//			{
			//      			fout1 << a[p] << endl;
			//      	}
			for (unsigned int j = p * p; j < n + 1; j += p)
			{
				a[j] = 0;
			}
		}
	}
	//End-----------------------------------------------------

	for (unsigned int i = 499999999; i <= n; i++)
	{
		if (a[i] == 0) // Пропускаем нули в массиве
		{
			continue;
		}
		if (Ferma(a[i] + 8) == false || Ferma(a[i] + 12) == false) // Т.к. уже известно, что взятое a[i] + 0 - простое, то проверяем a[i] + 10 на простоту.
		{
			continue;
		}
		if (Ferma(a[i] + 2) || Ferma(a[i] + 4) || Ferma(a[i] + 6) || Ferma(a[i] + 10)) // Если a[i] + 0, a[i] + 8 и a[i] + 12 - простые, то проверяем что остальные числа составные
		{
			continue;
		}
		// Если все условия выполнены, то увеличиваем счётчик простых чисел и выводим число удовлетворяющее гипотезе.
		cp++;
		cs += 9;
		fout1 << a[i] << endl;
	}
	fout2 << "Количество простых чисел удовлетворяющих гипотезе: " << cp << endl;
	fout2 << "Количество cоставных чисел: " << cs << endl;
	fout2 << "Количество простых чисел в диапозоне от + 0 до + 10: " << cs / cp / 9 << endl;
	fout2 << "Количество составных чисел в диапозоне от + 0 до + 10: " << cs / cp << endl;
	fout1.close();
	fout2.close();
}