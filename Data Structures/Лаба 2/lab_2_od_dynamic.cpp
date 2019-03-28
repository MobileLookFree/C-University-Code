#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <cstdlib>

using namespace std;

void output(int *mas, int n) {
	for (int i = 0; i < n; i++)
	{
		cout << "Элемент массива [" << i + 1 << "]= " << mas[i] << endl;
	}
}

void handmas(int *mas, int sizemas) {
	for (int i = 0; i < sizemas; i++)
	{
		cout << "Элемент массива [" << i << "]= ";
		cin >> mas[i];
		if (mas[i] > 256) cout << "Неверный размер: < 256." << endl;
		while (mas[i] > 256)
		{
			cout << "Элемент массива [" << i << "]= ";
			cin >> mas[i];
			if (mas[i] > 256) cout << "Неверный размер: < 256." << endl;
		}

		if (mas[i] <1) cout << "Неверный размер; > 0." << endl;
		while (mas[i] < 1)
		{
			cout << "Элемент массива [" << i << "]= ";
			cin >> mas[i];
			if (mas[i] > 256) cout << "Неверный размер: < 256." << endl;
		}
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
	int N, elem, index;
	cout << "Введите размер массива: ";
	cin >> N;
	if (N < 1 || cin.fail())
		cout << "Неверно. Введите число от 1." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (N<1) {
		cout << "Введите размер массива: ";
		cin >> N;
		if (N<1 || cin.fail()) cout << "Неверно. Введите число от 1." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	int *mas;
	mas = new int[N];

	handmas(mas, N);
	cout << endl;

	cout << "Введите элемент для замены: ";
	cin >> elem;
	cout << "Введите позицию: ";
	cin >> index;

	mas = (int *)realloc((void *)mas, (N = N + 1) * sizeof(int));
	for (int i = N; i > index - 1; i--) {
		mas[i] = mas[i - 1];
	}
	mas[index - 1] = elem;

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