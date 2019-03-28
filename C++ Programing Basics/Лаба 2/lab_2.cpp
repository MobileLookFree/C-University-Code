#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian"); //�����������
	int a = 2, b = 3, c = 5, answer; //������������� a, b, c
	double y, x; //������������� x,y

	cout << "������� �������� x �� 1, �� ������ 6: ";
	cin >> x; //���� x
	if (x<1 || x>=6 || cin.fail()) //�������� �� �������� �������� � ��� ����������
	cout << "�������. ������� ����� �� 1, �� ������ 6." << endl;
	cin.clear(); //������� ������ ������� ������, ��������������� ����������� ����� ��������������
	cin.ignore(cin.rdbuf()->in_avail()); //������������� (ignore) ����������� �������� (avail) ������ (rdbuf)
	while (x<1 || x >= 6) {
		cout << "������� �����: ";
		cin >> x;
		if (x<1 || x >= 6 || cin.fail()) 
		cout << "�������. ������� ����� �� 1, �� ������ 6." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	//��������� �������� ������� ��� �������������� ��������� �
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
	

	cout << "�������� y: " << y << endl; //����� y
	cout << endl;
	
	system("Pause");
    return 0;
}

