#include<iostream>
#include <iomanip>
#include <math.h>
#include <cstdlib>

using namespace std;

template <typename T>
class Gauss
{
private:
	float **matrix;
	float *xTable;
	float **p;
	int equationNumber;
	int equationRate;
	bool flagDeterm = true;
public:
	Gauss(); //конструктор
	void checkMatrix(int n, int m); //проверка размера матрицы
	void setMatrix(int equationNumber, int equationRate, float **matrix); //инициализация матрицы
	float checkDeterm(int equationNumber, float **matrix); //проверка на вырожденность
	void checkDetermHelper(float **matrix, float **p, int i, int j, int equationNumber);
	void calculate(int equationNumber, int equationRate, float **matrix, float *xTable); //решение методом Гаусса
	void XmatrixOut(int equationNumber, int equationRate, float *xTable); //вывод столбца корней
};


//конструктор
template <typename T>
Gauss<T>::Gauss() {
}


//проверка размера матрицы
template <typename T>
void Gauss<T>::checkMatrix(int n, int m) {
	if (n !=m) { 
		cout << "Матрица не решается методом Гаусса. Введите новую матрицу: " << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}
	else {
		equationNumber = n; //инициализируем количество уравнений
		m += 1;
		equationRate = m; //инициализируем старшую степень уравнений
		setMatrix(equationNumber, equationRate, matrix);
	}
}


//инициализация матрицы
template <typename T>
void Gauss<T>::setMatrix(int equationNumber, int equationRate, float **matrix) {

	matrix = new float *[equationNumber];
	for (int i = 0; i < equationNumber; i++)
		matrix[i] = new float[equationRate];

	//инициализируем
	for (int i = 0; i < equationNumber; i++)

		for (int j = 0; j < equationRate; j++)
		{
			cout << "Элемент " << "[" << i + 1 << " , " << j + 1 << "]: ";
			cin >> matrix[i][j];
		}

	checkDeterm(equationNumber, matrix);

	if (flagDeterm = false) {
		cout << "Введите матрицу заново:" << endl;
		flagDeterm = true;
		setMatrix(equationNumber, equationRate, matrix);
	}
	else {
		calculate(equationNumber, equationRate, matrix, xTable);
	}
}


// проверка на вырожденность
template <typename T>
float Gauss<T>::checkDeterm(int equationNumber, float **matrix) {

	//рекурсивное вычисление определителя

	int i, j, k, n;
	float d;
	p = new float*[equationNumber];
	for (i = 0; i < equationNumber; i++)
		p[i] = new float[equationNumber];
	j = 0; d = 0;
	k = 1; //(-1) в степени i
	n = equationNumber - 1;

	if (equationNumber == 1) {
		d = matrix[0][0];
		cout << endl;
		cout << "Определитель матрицы равен " << d << endl;
		return(d);
	}

	if (equationNumber == 2) {
		d = matrix[0][0] * matrix[1][1] - (matrix[1][0] * matrix[0][1]);
		cout << endl;
		cout << "Определитель матрицы равен " << d << endl;
		return(d);
	}

	if (equationNumber>2) {
		for (i = 0; i<equationNumber; i++) {
			checkDetermHelper(matrix, p, i, 0, equationNumber);
			cout << matrix[i][j] << endl;
			d = d + k * matrix[i][0] * checkDeterm(n, p);
			k = -k;
		}
	}

	if (d == 0) {
		flagDeterm = false;
	}
	return(d);
}


template <typename T>
void Gauss<T>::checkDetermHelper(float **matrix, float **p, int i, int j, int equationNumber) {
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < equationNumber - 1; ki++) { // проверка индекса строки
		if (ki == i) di = 1;
		dj = 0;
		for (kj = 0; kj < equationNumber - 1; kj++) { // проверка индекса столбца
			if (kj == j) dj = 1;
			p[ki][kj] = matrix[ki + di][kj + dj];
		}
	}
}


//решение методом Гаусса
template <typename T>
void Gauss<T>::calculate(int equationNumber, int equationRate, float **matrix, float *xTable) {

	//выводим массив
	cout << "Исходная матрица: " << endl;
	for (int i = 0; i<equationNumber; i++)
	{
		for (int j = 0; j<equationRate; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	cout << endl;

	//приведение к верхнетреугольному виду
	float temp;
	xTable = new float[equationRate];
	int k;

	for (int i = 0; i<equationNumber; i++) {
		temp = matrix[i][i];

		for (int j = equationNumber; j >= i; j--)
			matrix[i][j] /= temp;
		for (int j = i + 1; j<equationNumber; j++)
		{
			temp = matrix[j][i];
			for (int k = equationNumber; k >= i; k--)
				matrix[j][k] -= temp*matrix[i][k];
		}
	}

	xTable[equationNumber - 1] = matrix[equationNumber - 1][equationNumber];

	for (int i = equationNumber - 2; i >= 0; i--) {
		xTable[i] = matrix[i][equationNumber];

		for (int j = i + 1; j < equationNumber; j++) {
			xTable[i] -= matrix[i][j] * xTable[j];
		}
	}

	XmatrixOut(equationNumber, equationRate, xTable);
}


//вывод столбца корней
template <typename T>
void Gauss<T>::XmatrixOut(int equationNumber, int equationRate, float *xTable) {

	cout << "Решения: " << endl;
	for (int i = 0; i < equationNumber; i++) {
		cout << "Корень " << i + 1 << ": " << xTable[i] << endl;
	}
	cout << endl;
}


void menu() {
	cout << endl;
	cout << "1. Найти решение системы линейных уравнений методом Гаусса: " << endl;
	cout << "2. Выйти: " << endl;
}


int main()
{
	setlocale(LC_ALL, "Russian");

	Gauss <float> myGauss;

	int choise, n, m;
	

	do {
		menu();
		cin >> choise;

		switch (choise)
		{
		case 1:

			cout << "Введи число уравнений: ";
			cin >> n;
			if (n < 1 || cin.fail())
				cout << "Неверно. Введите натуральное число." << endl;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			while (n < 1) {
				cout << "Введите натуральное число: ";
				cin >> n;
				if (n < 1 || cin.fail())
					cout << "Неверно. Введите натуральное число." << endl;
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
			}

			cout << "Введи число неизвестных: ";
			cin >> m;
			if (m < 1 || cin.fail())
				cout << "Неверно. Введите натуральное число." << endl;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			while (m < 1) {
				cout << "Введите натуральное число: ";
				cin >> m;
				if (m < 1 || cin.fail())
					cout << "Неверно. Введите натуральное число." << endl;
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
			}

			myGauss.checkMatrix(n, m);
			break;
		case 2:
			exit(0);
		default: cout << "Неверный пункт меню!" << endl;
		}
	} while (choise != 2);


	system("Pause");
	return 0;
}