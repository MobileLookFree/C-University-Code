#include <iostream>
#include <cstdlib>
using namespace std;

int fact(int N)
{
	if (N < 0) // ���� ������������ ���� ������������� �����
		return 0; // ���������� ����
	if (N == 0) // ���� ������������ ���� ����,
		return 1; // ���������� ��������� �� ���� - �� �����������, �� ��� 1 =)
	else // �� ���� ��������� �������
		return N * fact(N - 1); // ������ ��������.
}

int main()
{
	int N = 0;
	while (N < 20) {
		cout << N << ": " << fact(N) << endl;
		N++;
	}

	system("Pause");
	return 0;
}