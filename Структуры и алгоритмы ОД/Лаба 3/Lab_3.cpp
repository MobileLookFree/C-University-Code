#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;


struct bus
{
	int number;
	double cost;
	char *time;
	char *date;
	bus *Next;
};

class List
{
	bus *Head;
public:
	List() { Head = NULL; }
	~List();
	void add();
	void show();
	void find();
};

List::~List() //���������� ������� �� �����
{
	while (Head != NULL)  //���� �� ������ �� ����� 
	{
		bus *temp = Head->Next; //��������� ���������� ��� �������� ������ ���������� ��������
		delete Head; //����������� ����� ������������ ������
		Head = temp; //������ ����� �� ���������
	}
}

void List::add() {
	    bus *temp = this->Head;
		temp = new bus;
		//�������� ������ ��� ����� �������

		cout << "������� ����� ��������: ";
		cin >> temp->number;


		cout << "������� ����� �����������: ";
		temp->time = new char[10];
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(temp->time, 10);

		cout << "������� ���� �����������: ";
		temp->date = new char[10];
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(temp->date, 10);


		cout << "������� ���� ������: ";
		cin >> temp->cost;
		cout << endl;

		//������ �������� ��������������� ����
		temp->Next = Head;//��������� ��������� ����

		this->Head = temp;

}



void List::show() //������� ����������� ������ �� ������
{
	bus *temp = this->Head; //���������� ���������, ������� ���������� �� ����� ������ ������ ������

	cout << "\n------------------------------------------------------------------";
	cout << "\n| ������� � | ����� ����������� | ���� ����������� | ���� ������ |";
	cout << "\n------------------------------------------------------------------\n";
	
	while (temp != NULL) //�� ��� ��� ���� �� �������� ������ ��������
	{
		cout << "|    " << setw(3) << temp->number << "    ";
		cout << "|         " << setw(5) << temp->time << "     ";
		cout << "|    " << setw(9) << temp->date << "     ";
		cout << "|     " << setw(4) << temp->cost << "    |";
		cout << "\n|           |                   |                  |             |\n";
		
		temp = temp->Next; //���������, ��� ����� ��� ����� ��������� �������
	}
	cout << "------------------------------------------------------------------\n";
}

void List::find() //������� ������ �������� �� ������
{
	bus *temp = this->Head; //���������� ���������, ������� ���������� �� ����� ������ ������ ������
	short number;//���������� ��� �������� ������ ��������

	cout << "\n" << "\t\t ������� ����� ������� ��� ��������: ";
	cin >> number;

	cout << "\n------------------------------------------------------------------";
	cout << "\n| ������� � | ����� ����������� | ���� ����������� | ���� ������ |";
	cout << "\n------------------------------------------------------------------\n";

	while (temp != NULL) //�� ��� ��� ���� �� �������� ������ ��������
	{
		if (temp->number == number)
		{
			cout << "|    " << setw(3) << temp->number << "    ";
			cout << "|         " << setw(5) << temp->time << "     ";
			cout << "|    " << setw(9) << temp->date << "     ";
			cout << "|     " << setw(4) << temp->cost << "    |";
			cout << "\n|           |                   |                  |             |\n";
		}

		temp = temp->Next; //���������, ��� ����� ��� ����� ��������� �������
	}
	cout << "------------------------------------------------------------------\n";
}



void menu()
{
	cout << "\t\t 1. ������� ����������:" << endl;
	cout << "\t\t 2. ������� ����������:" << endl;
	cout << "\t\t 3. ����� ������� � �������� �������:" << endl;
	cout << "\t\t 4. ������� ������� � �������:" << endl;
	cout << "\t\t 5. ���������� ������� ��������:" << endl;
	cout << "\t\t 6. �����:\n";
}


int main()
{
	setlocale(LC_ALL, "Russian");

	List bus_list;
	char c;

	do
	{
		menu();
		cin >> c;
		switch (c)
		{
		case '1': 
			bus_list.add();
			break;
		case '2': 
			bus_list.show();
			break;
		case '3':
			bus_list.find();
			break;
		case '6': break;
		default: cout << "�������� ����� ����!" << endl;
		}
		system("Pause");
		system("cls");

	} while (c != '6');


	system("Pause");
	return 0;
}