#include <iostream>
#include <cstdlib>

using namespace std;

unsigned int swap_bits(unsigned int n, int i, int j){
    unsigned int a, b;
    a = (n >> i) & 1;
    b = (n >> j) & 1;
    if(a != b)
        n = n & ~((1 << i) | (1 << j)) | (a << j) | (b << i);
    return n;
}
 
int main(){
	setlocale(LC_ALL, "Russian");
    unsigned int n;
    cout << "Введите исходное число: ";
    cin >> n;
 
	
    n = swap_bits(n, 0, 1);
    n = swap_bits(n, 2, 3);
    n = swap_bits(n, 4, 5);
    n = swap_bits(n, 6, 7);
    n = swap_bits(n, 8, 9);
    n = swap_bits(n, 10, 11);
    n = swap_bits(n, 12, 13);
    n = swap_bits(n, 14, 15);
    n = swap_bits(n, 16, 17);
    n = swap_bits(n, 18, 19);
    n = swap_bits(n, 20, 21);
    n = swap_bits(n, 22, 23);
    n = swap_bits(n, 24, 25);
    n = swap_bits(n, 26, 27);
    n = swap_bits(n, 28, 29);
    n = swap_bits(n, 30, 31);
    
    cout << "Конечное число: " << n <<endl;
    system("Pause");
    return 0;
}


