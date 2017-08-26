#include <iostream>   
#include <string> 
#include <cstring>
#include <cstdlib> 

using namespace std;

string finalchar; //строка, в которую записываются лишь символы от 0 до 9, A-Z

char numeral[36] = { '0','1','2','3','4','5','6','7','8','9', //все возможные цифры
'A','B','C','D','E','F','G','H','I','J','K','L','M','N',
'O','P','Q','R','S','T','U','V','W','X','Y','Z' };


char newsystem_number(int newnumber) { //функция записи числа из десятичной с.с. в новой
	return numeral[newnumber];
}


void ten_base(int newnumber, int newbase) { //функция подсчета числа из десятичной с.с. в систему с основанием newbase
	if (newnumber<newbase) {
		cout << newsystem_number(newnumber);
		return;
	}
	ten_base(newnumber / newbase, newbase);
	cout << newsystem_number(newnumber % newbase);
}


string filter(const string &to, const string &remove) //фильтр ввода числа, удаляющие из строки символы-аргументы функции
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
	int base, newbase; //введенное пользователем основание и основание той системы, в которую будет осуществлен перевод
	string number, temp; //введенное число, промежуточная переменная для хранинеия числа в верхнем регистре

	cout << "Введите положительное число: ";
	getline(cin, number); //ввод числа
	filter(number, "'\\,<\".<-+*&!?"); //фильтр ввода
	number = finalchar; //очищеннон от лишнего число

	char *chislo = new char[number.length() + 1]; //сивмольный массив, содержащий в себе введенное число
	strcpy(chislo, number.c_str());

	char up;
	int i = 0;
	while (chislo[i])
	{
		chislo[i] = toupper(chislo[i]); //все введенные символы становятся заглаными
		temp.push_back(toupper(chislo[i])); //запись заглавных чисел в temp
		i++;
	}
	number.clear();
	number = temp; //введенное число из заглавных символов


	cout << "Введите основание, не превышающее 36: "; //ввод начального основания числа
	cin >> base;

	if (base<2 || base>36 || cin.fail()) //проверка на ввод символов или значений, не принадлежащих промежутку
		cout << "Неверно. Введите число от 2 до 36." << endl;
	cin.clear(); //очистка потока вводных данных, предотвращающая циклический вывод предупреждения
	cin.ignore(cin.rdbuf()->in_avail()); //игнорирование (ignore) колличества символов (avail) буфера (rdbuf)
	while (base<2 || base >36) {
		cout << "Введите основание, не превышающее 36: ";
		cin >> base;
		if (base<2 || base>36 || cin.fail())
			cout << "Неверно. Введите число от 2 до 36." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}


	for (int j = 0; j<(number.length() + 1); j++) //проверка на соответсвие символам числа его основанию
	{
		for (int i = base; i<36; i++)
		{
			if (chislo[j] == numeral[i])
			{
				cout << "Неправильное основание системы счисления. Введите корректное: ";
				cin >> base;
				i = base;
				j = 0;
			}
		}
	}


	cout << "Введите новое основание системы счисления, не превышающее 36: "; //ввод нового основания числа
	cin >> newbase;

	if (newbase<2 || newbase>36 || cin.fail()) //проверка
		cout << "Неверно. Введите число от 2 до 36." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (newbase<2 || newbase >36) {
		cout << "Введите основание, не превышающее 36: ";
		cin >> newbase;
		if (newbase<2 || newbase>36 || cin.fail())
			cout << "Неверно. Введите число от 2 до 36." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	int newnumber = stoi(number, nullptr, base); //перевод числа из системы с указанным основанием в десятичную

	cout << endl;
	cout << "Число " << number << " в 10-ой системе счисления: " << newnumber << '\n';
	cout << endl;
	cout << "Число " << number << " в " << newbase << "-ой системе счисления: ";
	ten_base(newnumber, newbase); //запись числа из 10-ой системы счисления в желаемую пользователем
	cout << endl;
	cout << endl;
	cin.clear(); //очиска буфера ввода

	system("Pause");
	return 0;
}