#include <iostream>
#include <string>

using namespace std;

const int N = 200;

int main()
{
	setlocale(LC_ALL, "Russian");

	char *string = new char[N]; //указатель на строковый тип
	int curlen = 0, minlen = 200, index = 0, i; //минимальна€ длина
	cout << "¬ведите строку: ";
	cin.getline(string, 200);

	for (i = 0;; i++)
	{
		if (string[i] == ' ' || string[i] == '\0')
		{
			if (curlen<minlen) { //поиск минимального
				minlen = curlen;
				index = i;
			}
			if (string[i] == '\0')
				break;
			curlen = 0;
		}
		else curlen++;
	}
	cout << "Ќаименьшее колличество символов в слове:" << minlen << endl;
	cout << "Ќомер первой буквы наименьшего слова:" << index - minlen + 1 << endl;

	//system("Pause");
	return 0;
}
