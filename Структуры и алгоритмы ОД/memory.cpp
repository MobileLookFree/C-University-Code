#include <iostream>
#include <cstdlib>
using namespace std;

void coutp(unsigned x) {
	int n = sizeof(int) * 8;
	unsigned maska = (1 << n - 1);
	for (int i = 1; i <= n; i++) {
		cout << ((x&maska) >> n - i);
		maska = maska >> 1;
	}
}

int main()
{
	unsigned int x = 5, y , n = 2, test=6;
	x=x<< n;
	y = x >> n;
	cout << x << endl;
	cout << y << endl;
	x = 0; //���������� ����� ��� x � �������
	//������ 1
	unsigned maska = 1;
	maska = maska << 5;
	x = x | maska;
	cout << x << endl;
	//������ 2
	x = 0;
	maska = 1;
	//cout << x | (maska << 5) << endl;

	//���������� 7 � 5 ���� � �������
	maska = 160;
	x = 0;
	x = x | maska;
	cout << x << endl;
	//��������� ���������
	x = 0;
	x = ~x;
	cout << x << endl;
	maska = 1;
	maska = maska << 5;
	maska = ~maska;
	x = x&maska;
	cout << x << endl;
	coutp(test);
	cout << endl;
	system("Pause");
    return 0;
}

