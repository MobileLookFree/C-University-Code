#include <iostream>
#include <cstdlib>

using namespace std;

int sizemas; //���������� ������ �������

void randomas(int *mas) { //��������� ������� �������� ��������������� �����
	int randomansw;
	for (int i = 1; i <= sizemas; i++)
	{
		mas[i] = rand() % 1000;
	}
	cout << "���������� ������ - 0. ���������� - 1" << endl;
	cin >> randomansw;
	if (randomansw > 1) cout << "�������" << endl;
	while (randomansw > 1) {
		cout << "�����: ";
		cin >> randomansw;
		if (randomansw > 1) cout << "�������" << endl;
	}

	switch (randomansw) {
	case 0:
		for (int i = 1; i <= sizemas; i++)
		{
			cout << "������� ������� [" << i << "]= " << mas[i] << endl;
		}
		break;
	case 1:
		break;
	}
}

void handmas(int *mas) { //������ ���� �������
	for (int i = 1; i <= sizemas; i++)
	{
		cout << "������� ������� [" << i << "]= ";
		cin >> mas[i];
		if (mas[i] > 1000) cout << "�������� ������: < 1.000." << endl;
		while (mas[i] > 1000)
		{
			cout << "������� ������� [" << i << "]= ";
			cin >> mas[i];
			if (mas[i] > 1000) cout << "�������� ������: < 1.000." << endl;
		}

		if (mas[i] <1) cout << "�������� ������; > 0." << endl;
		while (mas[i] < 1)
		{
			cout << "������� ������� [" << i << "]= ";
			cin >> mas[i];
			if (mas[i] > 1000000) cout << "�������� ������: > 0." << endl;
		}
	}
}

void output(int *mas) { //����� ����������� �������
	for (int i = 1; i <= sizemas; i++)
	{
		cout << "������� ������� [" << i << "]= " << mas[i] << endl;
		delete [] mas;
	}
}

void max_heapify(int *mas, int i, int sizemas) //�������� � ��������� � ��������� �� ���
{
	int j, temp;
	temp = mas[i];
	j = 2 * i;
	while (j <= sizemas) //������ �������
	{
		if (j < sizemas && mas[j + 1] > mas[j])
			j = j + 1;
		if (temp > mas[j])
			break;
		else if (temp <= mas[j])
		{
			mas[j / 2] = mas[j];
			j = 2 * j;
		}
	}
	mas[j / 2] = temp;
	return;
}

void heapsort(int *mas, int sizemas) //����������
{
	int i, temp;
	for (i = sizemas; i >= 2; i--)
	{
		temp = mas[i];
		mas[i] = mas[1];
		mas[1] = temp;
		max_heapify(mas, 1, i - 1);
	}
}

void build_maxheap(int *mas, int sizemas) //������� ����(��������)
{
	int i;
	for (i = sizemas / 2; i >= 1; i--)
	{
		max_heapify(mas, i, sizemas);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int *mas = new int[sizemas];
	cout << "������� ������ �������: ";
	cin >> sizemas;
	if (sizemas < 1 || cin.fail())
		cout << "�������. ������� ����� �� 1." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (sizemas<1) {
		cout << "������� ������ �������: ";
		cin >> sizemas;
		if (sizemas<1 || cin.fail()) cout << "�������. ������� ����� �� 1." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	if (sizemas >= 10)
		randomas(mas);
	else handmas(mas);
	cout << endl;
	cout << "������ � ����������� ������������� �����������" << endl;
	cout << endl;
	build_maxheap(mas, sizemas);
	heapsort(mas, sizemas);
	output(mas);
	cout << endl;

	system("Pause");
	return 0;

}


