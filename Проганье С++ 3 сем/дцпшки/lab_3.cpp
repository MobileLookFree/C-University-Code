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
	cout << "������� n: ";
	cin >> n;
	if (n<1 || cin.fail())
		cout << "�������. ������� ����������� �����." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (n<1) {
		cout << "������� ����������� �����: ";
		cin >> n;
		if (n<1 || cin.fail()) cout << "�������. ������� ����������� �����." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	cout << "������������ �������=" << proizv(n) << endl;

	for (int i = 1; i <= n; i++)
	{
		sumall += proizv(i);
	}

	cout << "�����: " << sumall << endl;
	cout << endl;
	cout << "������� ����������� ���������? ������� 1 ��� �� ��������� � 0 ��� ���������� ���������." << endl;
	cin >> answer;
	if (answer<0 || answer>1 || cin.fail())
		cout << "�������. ������� 1 ��� �� ��������� � 0 ��� ���������� ���������." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (answer<0 || answer>1) {
		cout << "�������� �����: ";
		cin >> answer;
		if (answer < 0 || answer > 1 || cin.fail()) cout << "�������. ������� 1 ��� �� ��������� � 0 ��� ���������� ���������." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	switch (answer) {
	case 1:
		for (int i = 1; i <= n; i++)
		{
			cout << i << " ���������=" << proizv(i)<<endl;
		}
		break;
	case 0:
		exit(0);
		break;
	}

	system("Pause");
	return 0;
}