#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int a, b, c, *mas;
	
	cout << "������� a: ";
	cin >> a; 
	if (a<1 || cin.fail()) 
		cout << "�������. ������� ����������� �����." << endl;
	cin.clear(); 
	cin.ignore(cin.rdbuf()->in_avail()); 
	while (a <1) {
		cout << "������� a: ";
		cin >> a;
		if (a<1 || cin.fail())
			cout << "�������. ������� ����������� �����." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	mas = new int[a];

	cout << "������� b: ";
	cin >> b;
	if (b<1 || cin.fail())
		cout << "�������. ������� ����������� �����." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (b <1) {
		cout << "������� b: ";
		cin >> b;
		if (b<1 || cin.fail())
			cout << "�������. ������� ����������� �����." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	cout << "������� c: ";
	cin >> c;
	if (c<1 || cin.fail())
		cout << "�������. ������� ����������� �����." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (c <1) {
		cout << "������� c: ";
		cin >> c;
		if (c<1 || cin.fail())
			cout << "�������. ������� ����������� �����." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	int delta = c - b + 1;

	for (int i = 1; i <= a; i++)

	{
		mas[i] = rand() % delta + b;
	}

	cout << endl;
	cout << "������:" << endl;
	for (int i = 1; i <= a; i++)
	{
		cout << "������� ������� [" << i << "]= " << mas[i] << endl;
	}

	system("Pause");
    return 0;
}

