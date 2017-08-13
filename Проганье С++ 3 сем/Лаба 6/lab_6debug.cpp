#include <iostream>
#include <cstdlib>

using namespace std;

void allocarray(int* &p, int n) {
	p = new int[n];
}

void releaseArray(int* &p) {
	delete [] p;
}

void randomas(int *mas, int n) { //заполение массива датчиком псевдослучайных чисел
	int randomansw;
	for (int i = 1; i <= n; i++)
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
		for (int i = 1; i <= n; i++)
		{
			cout << "Элемент массива [" << i << "]= " << mas[i] << endl;
		}
		break;
	case 1:
		break;
	}
}

void handmas(int *mas, int n) { //ручной ввод массива
	for (int i = 1; i <= n; i++)
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

void output(int *mas, int n) { //вывод полученного массива
	for (int i = 1; i <= n; i++)
	{
		cout << "Элемент массива [" << i << "]= " << mas[i] << endl;
	}
}

void max_heapify(int *mas, int i, int n) //работает с элеиентом и следующим за ним
{
	int j, temp;
	temp = mas[i];
	j = 2 * i;
	while (j <= n) //внутри массива
	{
		if (j < n && mas[j + 1] > mas[j])
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

void heapsort(int *mas, int n) //сортировка
{
	int i, temp;
	for (i = n; i >= 2; i--)
	{
		temp = mas[i];
		mas[i] = mas[1];
		mas[1] = temp;
		max_heapify(mas, 1, i - 1);
	}
}

void build_maxheap(int *mas, int n) //создаем кучу(пирамиду)
{
	int i;
	for (i = n / 2; i >= 1; i--)
	{
		max_heapify(mas, i, n);
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");

	int sizemas;
	int *mas;
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

	allocarray(mas, sizemas);

	if (sizemas >= 10)
		randomas(mas, sizemas);
	else handmas(mas, sizemas);

	cout << endl;
	cout << "Массив с примененной пирамидальной сортировкой" << endl;
	cout << endl;

	build_maxheap(mas, sizemas);
	heapsort(mas, sizemas);

	output(mas, sizemas);
	releaseArray(mas);

	system("Pause");
    return 0;
}

