#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	int **mas, answer, sizemas;
	double sum;
	cout << "������� ������ �������: ";
	cin >> sizemas;
	if (sizemas <1 || cin.fail())
		cout << "�������. ������� ����� �� 1." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (sizemas<1) {
		cout << "������ �������:";
		cin >> sizemas;
		if (sizemas < 1 || cin.fail()) cout << "�������. ������� ����� �� 1." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	mas = new int*[sizemas];
	for (int i = 0; i < sizemas; i++) {
		mas[i] = new int[sizemas];
	}
	
	cout << "������� ��������� ������ ������� - 1 ��� ���������� ���������� - 2?" << endl;
	cin >> answer;
	if (answer <1 || answer > 2 || cin.fail())
		cout << "�������. ������� 1 ��� 2." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (answer <1 || answer > 2) {
		cout << "��� �����: ";
		cin >> answer;
		if (answer < 1 || answer >2 || cin.fail()) cout << "�������. ������� 1 ��� 2." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	switch (answer) {
	case 1: //������ ���� �������
		for (int i = 0; i < sizemas; i++) {
			for (int j = 0; j < sizemas; j++) {
				cout << "������� " << i << " " << j << ": ";
				cin >> mas[i][j];
			}
			cout << endl;
		}
		break;

	case 2: //���������� ��������� �������
		for (int i = 0; i < sizemas; i++) {
			for (int j = 0; j < sizemas; j++) {
				mas[i][j] = rand() % 100;
			}
			cout << endl;
		}
		break;

	}

	cout << "��������� ������:" << endl;
	for (int i = 0; i < sizemas; i++) {
		for (int j = 0; j < sizemas; j++) {
			cout << mas[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	cout << "������ � �������������� ��������:" << endl;
	for (int k = 0; k < sizemas; k++) //������� ����� 
	{
		for (int i = 0; i < sizemas; i++)
		{
			for (int j = sizemas - 1; j > i; j--)
				if (mas[k][j] < mas[k][j - 1])
				{
					int tmp = mas[k][j];
					mas[k][j] = mas[k][j - 1];
					mas[k][j - 1] = tmp;
				}
		}
	}

	for (int i = 0; i < sizemas; i++) {
		for (int j = 0; j < sizemas; j++) {
			cout << mas[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	cout << "������� �������������� �������� �������:" << endl;
	for (int i = 0; i<sizemas; i++) {
		sum = 0;
		for (int j = 0; j<sizemas; j++) {
			sum += mas[j][i]; //����� �������
		}
		cout << "������� " << i + 1 << " = " << sum/sizemas << endl;
	}
	cout << endl;

	system("Pause");
    return 0;
}

