#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int a, b, c, *mas;
	
	cout << "Введите a: ";
	cin >> a; 
	if (a<1 || cin.fail()) 
		cout << "Неверно. Введите натуральное число." << endl;
	cin.clear(); 
	cin.ignore(cin.rdbuf()->in_avail()); 
	while (a <1) {
		cout << "Введите a: ";
		cin >> a;
		if (a<1 || cin.fail())
			cout << "Неверно. Введите натуральное число." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	mas = new int[a];

	cout << "Введите b: ";
	cin >> b;
	if (b<1 || cin.fail())
		cout << "Неверно. Введите натуральное число." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (b <1) {
		cout << "Введите b: ";
		cin >> b;
		if (b<1 || cin.fail())
			cout << "Неверно. Введите натуральное число." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	cout << "Введите c: ";
	cin >> c;
	if (c<1 || cin.fail())
		cout << "Неверно. Введите натуральное число." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (c <1) {
		cout << "Введите c: ";
		cin >> c;
		if (c<1 || cin.fail())
			cout << "Неверно. Введите натуральное число." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	int delta = c - b + 1;

	for (int i = 1; i <= a; i++)

	{
		mas[i] = rand() % delta + b;
	}

	cout << endl;
	cout << "Массив:" << endl;
	for (int i = 1; i <= a; i++)
	{
		cout << "Элемент массива [" << i << "]= " << mas[i] << endl;
	}

	system("Pause");
    return 0;
}

