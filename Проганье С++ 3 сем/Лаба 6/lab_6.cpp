#include <iostream>
#include <cstdlib>

using namespace std;

int sizemas; //глобальный размер массива

void randomas(int *mas) { //заполение массива датчиком псевдослучайных чисел
	int randomansw;
	for (int i = 1; i <= sizemas; i++)
	{
		mas[i] = rand() % 1000;
	}
	cout << "Посмотреть массив - 0. Пропустить - 1" << endl;
	cin >> randomansw;
	if (randomansw > 1) cout << "Неверно" << endl;
	while (randomansw > 1) {
		cout << "Выбор: ";
		cin >> randomansw;
		if (randomansw > 1) cout << "Неверно" << endl;
	}

	switch (randomansw) {
	case 0:
		for (int i = 1; i <= sizemas; i++)
		{
			cout << "Элемент массива [" << i << "]= " << mas[i] << endl;
		}
		break;
	case 1:
		break;
	}
}

void handmas(int *mas) { //ручной ввод массива
	for (int i = 1; i <= sizemas; i++)
	{
		cout << "Элемент массива [" << i << "]= ";
		cin >> mas[i];
		if (mas[i] > 1000) cout << "Неверный размер: < 1.000." << endl;
		while (mas[i] > 1000)
		{
			cout << "Элемент массива [" << i << "]= ";
			cin >> mas[i];
			if (mas[i] > 1000) cout << "Неверный размер: < 1.000." << endl;
		}

		if (mas[i] <1) cout << "Неверный размер; > 0." << endl;
		while (mas[i] < 1)
		{
			cout << "Элемент массива [" << i << "]= ";
			cin >> mas[i];
			if (mas[i] > 1000000) cout << "Неверный размер: > 0." << endl;
		}
	}
}

void output(int *mas) { //вывод полученного массива
	for (int i = 1; i <= sizemas; i++)
	{
		cout << "Элемент массива [" << i << "]= " << mas[i] << endl;
		delete [] mas;
	}
}

void max_heapify(int *mas, int i, int sizemas) //работает с элеиентом и следующим за ним
{
	int j, temp;
	temp = mas[i];
	j = 2 * i;
	while (j <= sizemas) //внутри массива
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

void heapsort(int *mas, int sizemas) //сортировка
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

void build_maxheap(int *mas, int sizemas) //создаем кучу(пирамиду)
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
	cout << "Введите размер массива: ";
	cin >> sizemas;
	if (sizemas < 1 || cin.fail())
		cout << "Неверно. Введите число от 1." << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (sizemas<1) {
		cout << "Введите размер массива: ";
		cin >> sizemas;
		if (sizemas<1 || cin.fail()) cout << "Неверно. Введите число от 1." << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	}

	if (sizemas >= 10)
		randomas(mas);
	else handmas(mas);
	cout << endl;
	cout << "Массив с примененной пирамидальной сортировкой" << endl;
	cout << endl;
	build_maxheap(mas, sizemas);
	heapsort(mas, sizemas);
	output(mas);
	cout << endl;

	system("Pause");
	return 0;

}


