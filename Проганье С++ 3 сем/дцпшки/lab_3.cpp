#include <iostream>
#include <math.h>
#include <cmath>
#include <cstdlib>

using namespace std;

long double fact(int N)
{
	if (N < 0)
		return 0;
	if (N == 0)
		return 1;
	else
		return N * fact(N - 1);
}


long double proizv(int n) {
	long double sum, sum1, sumpart;
	int k;
	k = pow(n, 2);
	sum = fact(k);
	sumpart = fact(n - 1);

	if (sum == 1)
		sum1 = 1;
	else
		sum1 = sum / sumpart;
	return sum1;
}


int main() {
	setlocale(LC_ALL, "Russian");
	int n, k, i, answer;
	long double sum1, sumall = 0;
	cout << "Введите n: ";
	cin >> n;
	if (n<1 || cin.fail())
		cout << "Неверно. Введите натуральное число." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (n<1) {
		cout << "Введите натуральное число: ";
		cin >> n;
		if (n<1 || cin.fail()) cout << "Неверно. Введите натуральное число." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	cout << "Максимальный элемент=" << proizv(n) << endl;

	for (int i = 1; i <= n; i++)
	{
		sumall += proizv(i);
	}

	cout << "Сумма: " << sumall << endl;
	cout << endl;
	cout << "Желаете просмотреть слогаемые? Нажмите 1 для их просмотра и 0 для завершения программы." << endl;
	cin >> answer;
	if (answer<0 || answer>1 || cin.fail())
		cout << "Неверно. Нажмите 1 для их просмотра и 0 для завершения программы." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (answer<0 || answer>1) {
		cout << "Сделайте выбор: ";
		cin >> answer;
		if (answer < 0 || answer > 1 || cin.fail()) cout << "Неверно. Нажмите 1 для их просмотра и 0 для завершения программы." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	switch (answer) {
	case 1:
		for (int i = 1; i <= n; i++)
		{
			cout << i << " слогаемое=" << proizv(i)<<endl;
		}
		break;
	case 0:
		exit(0);
		break;
	}

	system("Pause");
	return 0;
}