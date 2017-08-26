#include <iostream>   
#include <string> 
#include <cstring>
#include <cstdlib> 

using namespace std;

string finalchar;

char numeral[36] = { '0','1','2','3','4','5','6','7','8','9',
'A','B','C','D','E','F','G','H','I','J','K','L','M','N',
'O','P','Q','R','S','T','U','V','W','X','Y','Z' };


char newsystem_number(int newnumber) {
	return numeral[newnumber];
}


void ten_base(int newnumber, int newbase) {
	if (newnumber<newbase) {
		cout << newsystem_number(newnumber);
		return;
	}
	ten_base(newnumber / newbase, newbase);
	cout << newsystem_number(newnumber % newbase);
}


string filter(const string &to, const string &remove)
{
	for (string::const_iterator it = to.begin(); it != to.end(); ++it)
	{
		if (remove.find(*it) == string::npos)
		{
			finalchar += *it;
		}
	}
	return finalchar;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int base, newbase;
	string number, temp;

	cout << "Введите положительное число: ";
	getline(cin, number);
	filter(number, "'\\,<\".<-+*&!?");
	number = finalchar;

	char *chislo = new char[number.length() + 1];
	strcpy(chislo, number.c_str());

	char up;
	int i = 0;
	while (chislo[i])
	{
		chislo[i] = toupper(chislo[i]);
		temp.push_back(toupper(chislo[i]));
		i++;
	}
	number.clear();
	number = temp;


	cout << "Введите основание, не превышающее 36: ";
	cin >> base;

	if (base<2 || base>36 || cin.fail())
		cout << "Неверно. Введите число от 2 до 36: ";
	cin.clear(); //очистка потока вводных данных, предотвращающая циклический вывод предупреждения
	cin.ignore(cin.rdbuf()->in_avail()); //игнорирование (ignore) колличества символов (avail) буфера (rdbuf)
	while (base<2 || base >36 || cin.fail()) {
		cout << "Введите основание, не превышающее 36: ";
		cin >> base;
		if (base<2 || base>36 || cin.fail())
			cout << "Неверно. Введите число от 2 до 36: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> newbase;
	}


	for (int j = 0; j<(number.length() + 1); j++)
	{
		for (int i = base; i<36; i++)
		{
			if (chislo[j] == numeral[i] || cin.fail())
				cout << "Неправильное основание системы счисления. Введите корректное: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			while (chislo[j] == numeral[i] || cin.fail()) {
				cin >> base;
				i = base;
				j = 0;
				if (chislo[j] == numeral[i] || cin.fail())
					cout << "Неверно. Введите число от 2 до 36: ";
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
			}
		}
	}


	cout << "Введите новое основание системы счисления, не превышающее 36: ";
	cin >> newbase;

	if (newbase<2 || newbase>36 || cin.fail())
		cout << "Неверно. Введите число от 2 до 36: ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (newbase<2 || newbase >36 || cin.fail()) {
		cout << "Введите основание, не превышающее 36: ";
		cin >> newbase;
		if (newbase<2 || newbase>36 || cin.fail())
			cout << "Неверно. Введите число от 2 до 36: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> newbase;
	}

	int newnumber = stoi(number, nullptr, base);

	cout << endl;
	cout << "Число " << number << " в 10-ой системе счисления: " << newnumber << '\n';
	cout << endl;
	cout << "Число " << number << " в " << newbase << "-ой системе счисления: ";
	ten_base(newnumber, newbase);
	cout << endl;
	cout << endl;

	system("Pause");
	return 0;
}