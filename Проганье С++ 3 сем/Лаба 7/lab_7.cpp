#include <iostream>
#include <list>
#include <iterator>
#include <cstdlib>

using namespace std;

int element, newelement, deleted, search, answer;
list<int> myList;

void menu_items() {
	cout << "������� ������ - 0" << endl;
	cout << "���������� ������ - 1" << endl;
	cout << "�������� ����� ������� � ����� - 2" << endl;
	cout << "�������� ����� ������� � ������ - 3" << endl;
	cout << "������� ������� �� ������. ������ �������� �������� - 4" << endl;
	cout << "������������� ������ �� ����������� - 5" << endl;
	cout << "�������� ������ - 6" << endl;
	cout << "��������� ��������� - 7" << endl;
	cout << endl;
}

int actions(int answer) {
	switch (answer) {
	case 0:
		int size;
		cout << "������� ����� ������: ";
		cin >> size;
		if (size < 1 || cin.fail())
			cout << "�������. ������� ����� �� 1." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		while (size<1) {
			cout << "������� ����� ������: ";
			cin >> size;
			if (size<1 || cin.fail()) cout << "�������. ������� ����� �� 1." << endl;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
		}

		for (int i = 1; i <= size; i++) {
			cout << "������� ������� ������ " << i << ": ";
			cin >> element;
			myList.push_back(element); // ��������� � ������ ����� ��������
		}
		cout << endl;
		break;

	case 1:
		copy(myList.begin(), myList.end(), ostream_iterator<int>(cout, " ")); // ����� �� ����� ��������� ������
		cout << endl;
		break;

	case 2:
		cout << "�������� ����� ������� � �����: " << endl;
		cin >> newelement;
		myList.push_back(newelement);
		cout << endl;
		break;

	case 3:
		cout << "�������� ����� ������� � ������: " << endl;
		cin >> newelement;
		myList.push_front(newelement);
		cout << endl;
		break;

	case 4:
		cout << "������� ������� �� ������. ������� �������� ��������: ";
		cin >> deleted;
		myList.remove(deleted);
		cout << endl;
		break;

	case 5:
		cout << "��������������� ������:" << endl;
		myList.sort();
		copy(myList.begin(), myList.end(), ostream_iterator<int>(cout, " "));
		cout << endl;
		break;

	case 6:
		cout << "������ ��� ������. ������� ������: ";
		myList.clear();
		copy(myList.begin(), myList.end(), ostream_iterator<int>(cout, " "));
		cout << endl;
		break;

	case 7:
		int answerend;
		cout << "�� ����� ������ �����? ������� 1 ��� ���������� ��������� � 0 - ��� ����������� ������: ";
		cin >> answerend;
		if (answerend <0 || answerend >1 || cin.fail())
			cout << "�������." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		while (answerend <0 || answerend >1) {
			cout << "�������� �����:";
			cin >> answerend;
			if (answerend <0 || answerend >1 || cin.fail()) cout << "�������." << endl;
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
		cout << "�������� �������� �������: ";
		cin >> answer;
		if (answer < 0 || answer > 7 || cin.fail())
			cout << "�������." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		while (answer < 0) {
			cout << "�������� �����: ";
			cin >> answer;
			if (answer < 0 || answer > 7 || cin.fail()) cout << "�������." << endl;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
		}
		actions(answer);
	}

	system("Pause");
    return 0;
}

