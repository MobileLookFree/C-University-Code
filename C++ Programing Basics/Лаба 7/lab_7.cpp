#include <iostream>
#include <list>
#include <iterator>
#include <cstdlib>

using namespace std;

int element, newelement, deleted, search, answer;
list<int> myList;

void menu_items() {
	cout << "Создать список - 0" << endl;
	cout << "Отобразить список - 1" << endl;
	cout << "Добавить новый элемент в конец - 2" << endl;
	cout << "Добавить новый элемент в начало - 3" << endl;
	cout << "Удалить элемент из списка. Ввести значение элемента - 4" << endl;
	cout << "Отсортировать список по возрастанию - 5" << endl;
	cout << "Очистить список - 6" << endl;
	cout << "Завершить программу - 7" << endl;
	cout << endl;
}

int actions(int answer) {
	switch (answer) {
	case 0:
		int size;
		cout << "Введите длину списка: ";
		cin >> size;
		if (size < 1 || cin.fail())
			cout << "Неверно. Введите число от 1." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		while (size<1) {
			cout << "Введите длину списка: ";
			cin >> size;
			if (size<1 || cin.fail()) cout << "Неверно. Введите число от 1." << endl;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
		}

		for (int i = 1; i <= size; i++) {
			cout << "Введите элемент списка " << i << ": ";
			cin >> element;
			myList.push_back(element); // добавляем в список новые элементы
		}
		cout << endl;
		break;

	case 1:
		copy(myList.begin(), myList.end(), ostream_iterator<int>(cout, " ")); // вывод на экран элементов списка
		cout << endl;
		break;

	case 2:
		cout << "Добавить новый элемент в конец: " << endl;
		cin >> newelement;
		myList.push_back(newelement);
		cout << endl;
		break;

	case 3:
		cout << "Добавить новый элемент в начало: " << endl;
		cin >> newelement;
		myList.push_front(newelement);
		cout << endl;
		break;

	case 4:
		cout << "Удалить элемент из списка. Введите значение элемента: ";
		cin >> deleted;
		myList.remove(deleted);
		cout << endl;
		break;

	case 5:
		cout << "Отсортированный список:" << endl;
		myList.sort();
		copy(myList.begin(), myList.end(), ostream_iterator<int>(cout, " "));
		cout << endl;
		break;

	case 6:
		cout << "Список был очищен. Текущий список: ";
		myList.clear();
		copy(myList.begin(), myList.end(), ostream_iterator<int>(cout, " "));
		cout << endl;
		break;

	case 7:
		int answerend;
		cout << "Вы точно хотите выйти? Введите 1 для завершения программы и 0 - для продолжения работы: ";
		cin >> answerend;
		if (answerend <0 || answerend >1 || cin.fail())
			cout << "Неверно." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		while (answerend <0 || answerend >1) {
			cout << "Сделайте выбор:";
			cin >> answerend;
			if (answerend <0 || answerend >1 || cin.fail()) cout << "Неверно." << endl;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
		}
		switch (answerend) {
		case 0:
			break;
		case 1:
			exit(0);
		}
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	menu_items();

	for (int i = 0; i < 100; i++) {
		cout << "Выберете желаемую функцию: ";
		cin >> answer;
		if (answer < 0 || answer > 7 || cin.fail())
			cout << "Неверно." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		while (answer < 0) {
			cout << "Сделайте выбор: ";
			cin >> answer;
			if (answer < 0 || answer > 7 || cin.fail()) cout << "Неверно." << endl;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
		}
		actions(answer);
	}

	system("Pause");
    return 0;
}

