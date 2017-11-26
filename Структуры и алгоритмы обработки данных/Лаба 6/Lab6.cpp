#include <iostream>
#include <cstdlib>
#include <ostream>
#include <iomanip>

using namespace std;


class Array
{
	friend istream &operator>> (istream &, Array &); // ������������� �������� �����
private:
	float *ptr; // ��������� �� ������
	int size; // ������ �������
public:
	Array(); // ����������� �� ���������
	Array(int); // ����������� � �����������
	Array(const Array &); // ����������� �����
	~Array(); // �����������
	int getSize() const;
	bool operator== (const Array &) const; // �������� ���������
	Array &operator- (const int &); // �������� �������� �������� �� �����
	float &operator[] (int);
	void setArray(); // ���������� �������
	void getArray(); // ����� �������
	void compare(const Array &) const; //�������� �� ������� ��������� �������
};


Array::Array() // ����������� �� ���������, ��� ����������
{
	size = 10; // �� ��������� ������ ������� = 10 ���������
	ptr = new float[size]; // �������� ����� � ������ ��� �������
	for (int ix = 0; ix < size; ix++) // �������� ������
		ptr[ix] = 0;
}


Array::Array(int arraySize) // ����������� � �����������
{
	// ���� �������� ��������� ������ 0, ��������� size �������� arraySize, ����� - 10
	size = (arraySize > 0 ? arraySize : 10);
	ptr = new float[size]; // �������� ����� � ������ ��� �������

	for (int ix = 0; ix < size; ix++) // �������� ������
		ptr[ix] = 0;
}


Array::Array(const Array &arrayToCopy) // ����������� �����
	:size(arrayToCopy.size)              // ������������� ������� �������
{
	ptr = new float[size]; // �������� ����� � ������ ��� �������

	for (int ix = 0; ix < size; ix++)
		ptr[ix] = arrayToCopy.ptr[ix]; // ��������� ������ ���������� ������� arrayToCopy
}


Array::~Array() // ����������� ������ Array
{
	delete[] ptr; // ���������� ������, ������ ������
}


int Array::getSize() const // ���������� ���������� ��������� �������
{
	return size;
}

bool Array::operator==(const Array &right) const// �������� ���������
{
	if (size != right.size)
		return false; // ������� � ������ ����������� ���������
	for (int ix = 0; ix < size; ix++)
		if (ptr[ix] != right.ptr[ix])
			return false; // ������� �� �����

	return true; // ������� �����
}


float &Array::operator[] (int subscript)
{
	if (subscript < 0 || subscript >= size)
	{
		std::cerr << "\n ������ �������: " << subscript << std::endl;
		exit(0); // ��������� ������ ���������, ������������ ������
	}
	return ptr[subscript]; // ������� ������ �� ������� �������
}


Array &Array::operator- (const int & key) // �������� �������� �������� �� �����
{
	int counterKey = 0; // ������� ��������� �������� ���������
						// ���������� ���������� ���������, ������� ���������� �������
	for (int ix = 0; ix < size; ix++)
	{
		if (ptr[ix] == key)
			counterKey++;
	}

	Array temp(size);
	temp = *this; // ��������� ������� ������ �� ��������� ������

	delete[] ptr; // j���������� ������
	size = size - counterKey; // �������������� ������

	ptr = new float[size];
	int counter = 0, ix = 0;
	while (counter < size)
	{
		if (temp[counter] != key)
		{
			ptr[ix] = temp.ptr[counter]; // ����������� ������
			ix++;
		}
		counter++;
	}

	return *this;
}


// ������������� �������� �����, ��� ����� �������� ������� � ����������
istream &operator>> (istream & input, Array &obj)
{
	for (int ix = 0; ix < obj.size; ix++)
		input >> obj.ptr[ix]; // ��������� ������ ������� obj
	return input; // ��������� ������������� ����, ���� cin >> x >> y >> z >> ...
}


void Array::setArray() // ���������� �������
{
	cout << "������� ������ �������: ";
	cin >> size;
	cout << "������� ������: " << endl;
	for (int ix = 0; ix < size; ix++) {
		cout << "������� " << ix << ": ";
		cin >> ptr[ix]; // ���� �������� ������� � ����������
	}
}


void Array::getArray() // ����� �������
{
	cout << "������: " << endl;
	for (int ix = 0; ix < size; ix++) {
		cout << setw(5) << ptr[ix]; // ����� ��������� ������� �� �����
	}

	cout << endl; // ����� ������
}


void Array::compare(const Array &right) const 
{
	for (int ix = 0; ix < size; ix++) {
		for (int ix = 0; ix < right.size; ix++) {
			if (ptr[ix] != right.ptr[ix] && ix>1) {
				ptr[ix-1] = ptr[ix];
				
			}	
		}
	}
}


void menu() {
	cout << "1. ������� 2 �������:" << endl;
	cout << "2. ������� �� �� �����:" << endl;
	cout << "3. �������� �������:" << endl;
	cout << "4. ������� �� ������� �������� �������:" << endl;
	cout << "5. �����:" << endl;
}


int main()
{
	setlocale(LC_ALL, "Russian");

	Array myArray1;
	Array myArray2;
	Array myArray3(myArray1);  // ������� ������ ������ Array, ��������� ����������� �����������

	myArray3 = myArray2; // ����������� ������� myArray3 ������ myArray2

	char c;
	
	do
	{
		menu();
		cin >> c;
		switch (c)
		{
		case '1':
			myArray1.setArray();
			myArray2.setArray();
			break;
		case '2':
			myArray1.getArray();
			myArray2.getArray();
			break;
		case '3':
			if (myArray1 == myArray2)
				cout << "������� myArray1 � myArray2 �����!" << endl;
			else
				cout << "������� myArray1 � myArray2 �� �����!" << endl;
			break;
		case '4':
			myArray1.compare(myArray2);
			myArray1.getArray();
			break;
		case '5':
			exit(0);
		default: cout << "�������� ����� ����!" << endl;
		}
		system("Pause");
		system("cls");

	} while (c != '5');

	system("Pause");
	return 0;
}

