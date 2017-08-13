#include <iostream>
#include <cstdlib>
using namespace std;

int fact(int N)
{
	if (N < 0) // если пользователь ввел отрицательное число
		return 0; // возвращаем ноль
	if (N == 0) // если пользователь ввел ноль,
		return 1; // возвращаем факториал от нуля - не удивляетесь, но это 1 =)
	else // Во всех остальных случаях
		return N * fact(N - 1); // делаем рекурсию.
}

int main()
{
	int N = 0;
	while (N < 20) {
		cout << N << ": " << fact(N) << endl;
		N++;
	}

	system("Pause");
	return 0;
}