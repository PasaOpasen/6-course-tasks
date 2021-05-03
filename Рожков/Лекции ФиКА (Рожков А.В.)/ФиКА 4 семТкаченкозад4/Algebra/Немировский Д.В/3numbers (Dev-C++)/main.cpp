#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

long long gcd(long long a, long long b) // ���������� ��� �� ��������� �������
{
	if(b==0)
		return a;
	return gcd(b, a % b);
}

long long mul(long long a, long long b, long long m) //��������������� ������� ��� pows
{
  long long q = (long long)((long double)a * (long double)b / (long double)m);
  long long r = a * b - q * m;
  return (r + 5 * m) % m;
}

long long pows(long long a, long long b, long long m) // ������� ���������� � ������� �� ������
{
	if(b==0)
		return 1;
	if(b % 2 == 0)
	{
		long long t = pows(a, b/2, m);
		return mul(t , t, m) % m;
	}
	return (mul(pows(a, b-1, m), a, m)) % m;
}

//���� �����------------------------------
bool Ferma(long long x)
{
	if(x == 2)
		return true;
	srand(time(NULL));
	for(int i=0; i < 100; i++)
	{
		long long a = (rand() % (x - 2)) + 2;
		if (gcd(a, x) != 1)
			return false;			
		if(pows(a, x-1, x) != 1)		
			return false;			
	}
	return true;
}
//End----------------------------------------

int main()
{
	setlocale(LC_ALL, "RUS");
	ofstream fout1("����� ��������������� ��������.txt");
	ofstream fout2("���������� ������� � ��������� �����.txt");
	unsigned int n, cp = 0, kp = 1, ks = 9;
	cout << "������� n: ";
	//cin >> n;
	n = 500000000;
	unsigned int *a = new unsigned int[n + 1]; // ��������� ������ ������� ����� ������ ����� ����� ����� ��� �������� ��������
	//������ ����������
	for (unsigned int i = 0; i < n + 1; i++)
	{
    	a[i] = i;
  	}
	for (unsigned int p = 2; p < n + 1; p++)
	{
    	if (a[p] != 0)
    	{	
			//��� �������: ����� ���� ������� �����
			//fout1 << a[p] << endl;
      		for (unsigned int j = p*p; j < n + 1; j += p)
      		{
       			a[j] = 0;
       		}
    	}
  	}
  	//End-----------------------------------------------------
  	
  	for (unsigned int i = 0; i <= n; i++) // ������ ��� ����� - ��� 0 � 1, ���������� �� � �������� ������� � 2
	{
		if (a[i] == 0) // ���������� ���� � �������
		{
			continue;
		}
		if ( Ferma(a[i] + 8) == false || Ferma(a[i] + 12) == false) // �.�. ������ a[i] + 0 - �������, �� ��������� a[i] + 8 � + 12 �� ��������
		{
			continue;
		}
		if (Ferma(a[i] + 2) || Ferma(a[i] + 4) || Ferma(a[i] + 6) || Ferma(a[i] + 10) ) // ���� a[i] + 0 � a[i] + 10 - �������, �� ��������� ��� ��������� ����� ���������
		{
			continue;
		}
		// ���� ��� ������� ���������, �� ����������� ������� ������� ����� � ������� ����� ��������������� ��������
		cp++;
		fout1 << a[i] << endl;
	}
	fout2 << "���������� ������� ����� ��������������� ��������: " << cp << endl;
	fout2 << "���������� c�������� �����: " << cp*9 << endl;
	fout2 << "���������� ������� ����� � ��������� �� + 0 �� + 10: " << kp << endl;
	fout2 << "���������� ��������� ����� � ��������� �� + 0 �� + 10: " << ks << endl;
	fout1.close();
	fout2.close();
}
