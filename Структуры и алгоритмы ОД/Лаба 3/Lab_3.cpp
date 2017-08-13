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

List::~List() //Деструктор вынесен за класс
{
	while (Head != NULL)  //Пока по адресу не пусто 
	{
		bus *temp = Head->Next; //Временная переменная для хранения адреса следующего элемента
		delete Head; //Освобождаем адрес обозначающий начало
		Head = temp; //Меняем адрес на следующий
	}
}

void List::add() {
	    bus *temp = this->Head;
		temp = new bus;
		//выделяем память под новый элемент

		cout << "Введите номер автобуса: ";
		cin >> temp->number;


		cout << "Введите время отправления: ";
		temp->time = new char[10];
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(temp->time, 10);

		cout << "Введите дату отправления: ";
		temp->date = new char[10];
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(temp->date, 10);


		cout << "Введите цену билета: ";
		cin >> temp->cost;
		cout << endl;

		//вводим значение информационного поля
		temp->Next = Head;//обнуление адресного поля

		this->Head = temp;

}



void List::show() //Функция отображения списка на экране
{
	bus *temp = this->Head; //Определяем указатель, который изначально он равен адресу начала списка

	cout << "\n------------------------------------------------------------------";
	cout << "\n| Автобус № | Время отправления | Дата отправления | Цена билета |";
	cout << "\n------------------------------------------------------------------\n";
	
	while (temp != NULL) //До тех пор пока не встретит пустое значение
	{
		cout << "|    " << setw(3) << temp->number << "    ";
		cout << "|         " << setw(5) << temp->time << "     ";
		cout << "|    " << setw(9) << temp->date << "     ";
		cout << "|     " << setw(4) << temp->cost << "    |";
		cout << "\n|           |                   |                  |             |\n";
		
		temp = temp->Next; //Указываем, что далее нам нужен следующий элемент
	}
	cout << "------------------------------------------------------------------\n";
}

void List::find() //Функция поиска автобуса по номеру
{
	bus *temp = this->Head; //Определяем указатель, который изначально он равен адресу начала списка
	short number;//Переменная для хранения номера автобуса

	cout << "\n" << "\t\t Введите номер нужного вам автобуса: ";
	cin >> number;

	cout << "\n------------------------------------------------------------------";
	cout << "\n| Автобус № | Время отправления | Дата отправления | Цена билета |";
	cout << "\n------------------------------------------------------------------\n";

	while (temp != NULL) //До тех пор пока не встретит пустое значение
	{
		if (temp->number == number)
		{
			cout << "|    " << setw(3) << temp->number << "    ";
			cout << "|         " << setw(5) << temp->time << "     ";
			cout << "|    " << setw(9) << temp->date << "     ";
			cout << "|     " << setw(4) << temp->cost << "    |";
			cout << "\n|           |                   |                  |             |\n";
		}

		temp = temp->Next; //Указываем, что далее нам нужен следующий элемент
	}
	cout << "------------------------------------------------------------------\n";
}



void menu()
{
	cout << "\t\t 1. Создать расписание:" << endl;
	cout << "\t\t 2. Вывести расписание:" << endl;
	cout << "\t\t 3. Найти автобус с заданным номером:" << endl;
	cout << "\t\t 4. Удалить автобус с номером:" << endl;
	cout << "\t\t 5. Количество выходов автобуса:" << endl;
	cout << "\t\t 6. Выйти:\n";
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
		default: cout << "Неверный пункт меню!" << endl;
		}
		system("Pause");
		system("cls");

	} while (c != '6');


	system("Pause");
	return 0;
}