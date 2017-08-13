#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian"); //русификация
	int a = 2, b = 3, c = 5, answer; //инициализация a, b, c
	double y, x; //инициализация x,y

	cout << "Введите значение x от 1, но меньше 6: ";
	cin >> x; //ввод x
	if (x<1 || x>=6 || cin.fail()) //проверка на диапазон значений и тип переменной
	cout << "Неверно. Введите число от 1, но меньше 6." << endl;
	cin.clear(); //очистка потока вводных данных, предотвращающая циклический вывод предупреждения
	cin.ignore(cin.rdbuf()->in_avail()); //игнорирование (ignore) колличества символов (avail) буфера (rdbuf)
	while (x<1 || x >= 6) {
		cout << "Введите число: ";
		cin >> x;
		if (x<1 || x >= 6 || cin.fail()) 
		cout << "Неверно. Введите число от 1, но меньше 6." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	//различные варианты функции при соответсвующих значениях х
	if (x >= 1 && x < 2)
		y = a + b*x + c*x*x;

	if (x >= 2 && x < 3)
		y = pow((a*sin(b*x)), 2);

	if (x >= 3 && x < 4)
		y = sqrt(abs(a + b*pow(x, 2))) + c;

	if (x >= 4 && x < 5)
		y = a*log(abs(b + (c / (2 * x))));

	if (x >= 5 && x < 6)
		y = exp(a*sin(x)) + pow(c, 3);
	

	cout << "Значение y: " << y << endl; //вывод y
	cout << endl;
	
	system("Pause");
    return 0;
}

