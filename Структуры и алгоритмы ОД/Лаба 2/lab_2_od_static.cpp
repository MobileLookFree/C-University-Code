#include <iostream>
#include <cstdlib>

using namespace std;

const int N = 15;

void output(int *mas, int n) { 
	for (int i = 0; i < n; i++)
	{
		cout << "Элемент массива [" << i+1 << "]= " << mas[i] << endl;
	}
}

int PowerOfTwo(int n)
{
	int InitValue = 1;
	while (InitValue < n)
		InitValue *= 2;
	if (InitValue == n)
		return 1;
	else
		return 0;
}

void proverkaTwo(int *mas, int n) {
	for (int i = 0; i < n; i++) {
		int k = 0;
		k = PowerOfTwo(mas[i]);
		if (k == 1) {
			cout << mas[i] << " - степень 2. Введите новое число: ";
			cin >> mas[i];
		}
	}
}

int Polindrom(int num1)
{
	int a, b;
	if (num1 > 10 && num1 < 100)
	{
		a = num1 / 10;
		b = num1 % 10;
		if (a == b)
		{
			return 1;
		}
	}

	if (num1 > 100 && num1 < 256)
	{
		a = num1 / 100;
		b = num1 % 10;

		if (a == b)
		{
			return 1;
		}
	}
}

void proverkaPolindrom(int *mas, int n) {
	for (int i = 0; i < n; i++) {
		int k = 0;
		k = Polindrom(mas[i]);
		if (k == 1) {
			cout << mas[i] << " - палиндром" << endl;
		}
	}
}

void sortirovka(int *mas, int n) {
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (mas[i] < mas[j])
			{
				int temp = mas[i];
				mas[i] = mas[j];
				mas[j] = temp;
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int mas[N] = { 1, 4, 5, 32, 23, 55, 128, 63, 37, 42, 9, 100, 87, 222, 71 };
	
	cout << "Исходный массив: " << endl;
	output(mas, N);
	cout << endl;

	proverkaTwo(mas, N);

	cout << "Обновленный массив: " << endl;
	output(mas, N);
	cout << endl;

	proverkaPolindrom(mas, N);
	cout << endl;

	cout << "Массив, отсортированный отностительно " << mas[0] << ": " << endl;
	sortirovka(mas, N);
	output(mas, N);
	cout << endl;

	system("Pause");
	return 0;
}

