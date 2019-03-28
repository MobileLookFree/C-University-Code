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
	Gauss(); //�����������
	void checkMatrix(int n, int m); //�������� ������� �������
	void setMatrix(int equationNumber, int equationRate, float **matrix); //������������� �������
	float checkDeterm(int equationNumber, float **matrix); //�������� �� �������������
	void checkDetermHelper(float **matrix, float **p, int i, int j, int equationNumber);
	void calculate(int equationNumber, int equationRate, float **matrix, float *xTable); //������� ������� ������
	void XmatrixOut(int equationNumber, int equationRate, float *xTable); //����� ������� ������
};


//�����������
template <typename T>
Gauss<T>::Gauss() {
}


//�������� ������� �������
template <typename T>
void Gauss<T>::checkMatrix(int n, int m) {
	if (n !=m) { 
		cout << "������� �� �������� ������� ������. ������� ����� �������: " << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}
	else {
		equationNumber = n; //�������������� ���������� ���������
		m += 1;
		equationRate = m; //�������������� ������� ������� ���������
		setMatrix(equationNumber, equationRate, matrix);
	}
}


//������������� �������
template <typename T>
void Gauss<T>::setMatrix(int equationNumber, int equationRate, float **matrix) {

	matrix = new float *[equationNumber];
	for (int i = 0; i < equationNumber; i++)
		matrix[i] = new float[equationRate];

	//��������������
	for (int i = 0; i < equationNumber; i++)

		for (int j = 0; j < equationRate; j++)
		{
			cout << "������� " << "[" << i + 1 << " , " << j + 1 << "]: ";
			cin >> matrix[i][j];
		}

	checkDeterm(equationNumber, matrix);

	if (flagDeterm = false) {
		cout << "������� ������� ������:" << endl;
		flagDeterm = true;
		setMatrix(equationNumber, equationRate, matrix);
	}
	else {
		calculate(equationNumber, equationRate, matrix, xTable);
	}
}


// �������� �� �������������
template <typename T>
float Gauss<T>::checkDeterm(int equationNumber, float **matrix) {

	//����������� ���������� ������������

	int i, j, k, n;
	float d;
	p = new float*[equationNumber];
	for (i = 0; i < equationNumber; i++)
		p[i] = new float[equationNumber];
	j = 0; d = 0;
	k = 1; //(-1) � ������� i
	n = equationNumber - 1;

	if (equationNumber == 1) {
		d = matrix[0][0];
		cout << endl;
		cout << "������������ ������� ����� " << d << endl;
		return(d);
	}

	if (equationNumber == 2) {
		d = matrix[0][0] * matrix[1][1] - (matrix[1][0] * matrix[0][1]);
		cout << endl;
		cout << "������������ ������� ����� " << d << endl;
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
	for (ki = 0; ki < equationNumber - 1; ki++) { // �������� ������� ������
		if (ki == i) di = 1;
		dj = 0;
		for (kj = 0; kj < equationNumber - 1; kj++) { // �������� ������� �������
			if (kj == j) dj = 1;
			p[ki][kj] = matrix[ki + di][kj + dj];
		}
	}
}


//������� ������� ������
template <typename T>
void Gauss<T>::calculate(int equationNumber, int equationRate, float **matrix, float *xTable) {

	//������� ������
	cout << "�������� �������: " << endl;
	for (int i = 0; i<equationNumber; i++)
	{
		for (int j = 0; j<equationRate; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	cout << endl;

	//���������� � ������������������ ����
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


//����� ������� ������
template <typename T>
void Gauss<T>::XmatrixOut(int equationNumber, int equationRate, float *xTable) {

	cout << "�������: " << endl;
	for (int i = 0; i < equationNumber; i++) {
		cout << "������ " << i + 1 << ": " << xTable[i] << endl;
	}
	cout << endl;
}


void menu() {
	cout << endl;
	cout << "1. ����� ������� ������� �������� ��������� ������� ������: " << endl;
	cout << "2. �����: " << endl;
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

			cout << "����� ����� ���������: ";
			cin >> n;
			if (n < 1 || cin.fail())
				cout << "�������. ������� ����������� �����." << endl;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			while (n < 1) {
				cout << "������� ����������� �����: ";
				cin >> n;
				if (n < 1 || cin.fail())
					cout << "�������. ������� ����������� �����." << endl;
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
			}

			cout << "����� ����� �����������: ";
			cin >> m;
			if (m < 1 || cin.fail())
				cout << "�������. ������� ����������� �����." << endl;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			while (m < 1) {
				cout << "������� ����������� �����: ";
				cin >> m;
				if (m < 1 || cin.fail())
					cout << "�������. ������� ����������� �����." << endl;
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
			}

			myGauss.checkMatrix(n, m);
			break;
		case 2:
			exit(0);
		default: cout << "�������� ����� ����!" << endl;
		}
	} while (choise != 2);


	system("Pause");
	return 0;
}