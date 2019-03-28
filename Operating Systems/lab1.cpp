#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <vector>
//#include <filesystem> //библиотека для для очистки файла

using namespace std;

int checkEnd[] = { 0, 0, 0, 0 }; //Массив флагов для проверки окончания работы потоков
int threadEnd[] = { 0, 0, 0, 0 }; //Массив флагов для проверки выхода потоков из цикла

string input = ""; //Строка для считывания с консоли
string output = ""; //Строка вывода
string outputTen = ""; //Строка вывода
string outputTwenty = ""; //Строка вывода
int choice; //Выбор в меню

fstream firstFile; //Переменная для работы с первым файлом
fstream secondFile; //Переменная для работы со вторым файлом

//Флаги
int writeOneNumber = 0; //Флаг записи одного числа в первый файл
int writeTwoNumbers = 0; //Флаг записи 2 чисел в первый файл
int firstFileWriteCheck = 0; //Флаг, показывающий, производилась ли запись в первый файл
int secondFileWriteCheck = 0; //Флаг, показывающий, производилась ли запись во второй файл
int firstFileCheck = 0; //Семафор доступа к первому файлу
int secondFileCheck = 0; //Семафор доступа ко второму файлу

//Счетчики
int startUpsOfSecond = 0; //Счетчик количества запусков второго потока
int startUpsOfThird = 0; //Счетчик количества запусков третьего потока

bool checkInput(string &symbolNumber) { //Функция проверки введённой строки по ASCII
    
    if ((int)symbolNumber[0] == 48 || (int)symbolNumber[0] < 48 || (int)symbolNumber[0] > 57) //48 - ноль, 57 - девять
        return false;
    for (int i = 1; i < symbolNumber.length(); i++) {
        if ((int)symbolNumber[i] < 48 || (int)symbolNumber[i] > 57)
            return false;
    }
    return true;
}

void writeIntoFile() {//Функция записи в первый файл
    
    vector <int> intNum; //Вектор для хранения чисел, пока первый файл занят
    
    while (threadEnd[0] == 0 || intNum.size() > 0) {
        if (input != "0") {
            cin >> input;
            
            if (input == "0")
                threadEnd[0] = 1;
            if (checkInput(input)) {
                intNum.push_back(atoi(input.c_str()));
                output.append(input);
                output.append(" ");
            }
            else {
                if (input != "0")
                    cout << "Ошибка ввода!" << endl;
            }
        }
        
        if (firstFileCheck == 0 && intNum.size() > 0) {
            firstFileCheck = 1;
            firstFile.open("file1.txt", ios::out | ios::app);
            
            while (intNum.size() > 0) {
                firstFile << intNum.front() << endl;
                intNum.erase(intNum.begin());
            }
            
            //Оповещение для второго потока, что в первый файл были записаны числа
            firstFileWriteCheck = 1;
            firstFile.close();
            firstFileCheck = 0;
        }
    }
    checkEnd[0] = 1;
}

void sumFunc() {// Функция записи сумм пар чисел из первого файла во второй
    
    string strNum; // Строка для считывания чисел из файла
    vector <int> numArr;
    
    while (threadEnd[1] == 0 || checkEnd[3] == 0 || firstFileWriteCheck != 0) {
        this_thread::sleep_for(chrono::seconds(1));
        
        if (firstFileCheck == 0 && secondFileCheck == 0 && firstFileWriteCheck != 0) {
            firstFileCheck = 1;
            secondFileCheck = 1;
            firstFile.open("file1.txt", ios::in);
            secondFile.open("file2.txt", ios::out | ios::app);
            
            //Считывание чисел из первого файла
            while (!firstFile.eof()) {
                getline(firstFile, strNum, '\n');
                
                if (strNum != "")
                    numArr.push_back(atoi(strNum.c_str()));
            }
            
            firstFile.close();
            firstFile.open("file1.txt", ios::out | ios::trunc);
            
            //Запись последнего числа обратно в файл, если чисел нечётное количество
            if (numArr.size() % 2 == 1) {
                firstFile << numArr[numArr.size() - 1];
                firstFile << endl;
                numArr.pop_back();
            }
            firstFileWriteCheck = 0;
            firstFileCheck = 0;
            firstFile.close();
            
            if (numArr.size() > 0) {
                for (int i = 0; i < numArr.size(); i = i + 2) {
                    secondFile << numArr[i] + numArr[i + 1];
                    secondFile << endl;
                    startUpsOfSecond++;
                }
                //Оповещение для третьего потока, что во второй файл были записаны числа
                secondFileWriteCheck = 1;
            }
            secondFile.close();
            numArr.clear();
            secondFileCheck = 0;
        }
        if (input == "0")
            threadEnd[1] = 1;
    }
    checkEnd[1] = 1;
    return;
}

void writeFile() { // Функция вывода чисел из второго файла
    string strNum;
    while (threadEnd[2] == 0 || checkEnd[1] == 0 || secondFileWriteCheck != 0) {
        this_thread::sleep_for(chrono::seconds(1));
        
        if (secondFileCheck == 0 && secondFileWriteCheck != 0) {
            secondFileCheck = 1;
            secondFile.open("file2.txt", ios::in | ios::out);
            
            startUpsOfThird++;
            if (startUpsOfThird % 20 == 0) //cчетчик 20х запусков
                writeTwoNumbers = 1;
            
            cout << "\nВывод: ";
            
            while (!secondFile.eof()) {
                getline(secondFile, strNum, '\n');
                if (strNum != "")
                    cout << strNum << " ";
            }
            
            secondFileWriteCheck = 0;
            secondFile.close();
            //Обнуление второго файла
            //experimental::filesystem::resize_file("file2.txt", 0);
            secondFileCheck = 0;
        }
        if (input == "0")
            threadEnd[2] = 1;
    }
    checkEnd[2] = 1;
    return;
}

void addNumbers() {// Функция добавления случайных чисел в 1 и 2 файлы
    int secondWorked = 0;
    int thirdWorked = 0;
    
    while (threadEnd[3] == 0 || checkEnd[0] == 0 || writeOneNumber != 0 || secondFileWriteCheck != 0) {
        if (startUpsOfSecond > 0 && startUpsOfSecond % 5 == 0) //каждое десятое
            writeOneNumber = 1;
        
        //Запись одного числа в первый файл при каждом 10 срабатывании 2-го потока
        if (writeOneNumber != 0) {
            while (firstFileCheck != 0) {}
            
            int addedNumber = (rand() % 500);
            string addedNumberString = to_string(addedNumber);
            
            firstFileCheck = 1;
            firstFile.open("file1.txt", ios::in | ios::app);
            firstFile << addedNumber << endl;
            
            output.append(addedNumberString);
            output.append(" ");
            outputTen.append(addedNumberString);
            outputTen.append(" ");
            
            firstFileWriteCheck = 1;
            writeOneNumber = 0;
            secondWorked += 10;
            startUpsOfSecond -= 10;
            firstFile.close();
            firstFileCheck = 0;
        }
        
        //Запись двух числе в первый файл при каждом 20 срабатывании 3-го потока
        if (writeTwoNumbers != 0) {
            while (firstFileCheck != 0) {}
            
            int addedNumberFirst = (rand() % 1000);
            string addedNumberFirstString = to_string(addedNumberFirst);
            
            int addedNumberSecond = (rand() % 2000);
            string addedNumberSecondString = to_string(addedNumberSecond);
            
            firstFileCheck = 1;
            firstFile.open("file1.txt", ios::in | ios::app);
            firstFile << addedNumberFirst << endl << addedNumberSecond << endl;
            
            output.append(addedNumberFirstString);
            output.append(" ");
            output.append(addedNumberSecondString);
            output.append(" ");
            
            outputTwenty.append(addedNumberFirstString);
            outputTwenty.append(" ");
            outputTwenty.append(addedNumberSecondString);
            outputTwenty.append(" ");
            
            writeTwoNumbers = 0;
            firstFileWriteCheck = 1;
            thirdWorked += 10;
            startUpsOfThird -= 10;
            firstFile.close();
            firstFileCheck = 0;
        }
        
        if (input == "0")
            threadEnd[3] = 1;
    }
    
    cout << "Второй поток отработал " << startUpsOfSecond + secondWorked << " раз" << endl;
    cout << "Третий поток отработал " << startUpsOfThird + thirdWorked << " раз" << endl;
    
    checkEnd[3] = 1;
}

void menu() {
    cout << "Вводите натуралные числа по одной на строку. Для завершения программы нажмите 0" << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    
    vector <thread> threads;
    
    threads.push_back(thread(writeIntoFile));
    threads.push_back(thread(sumFunc));
    threads.push_back(thread(writeFile));
    threads.push_back(thread(addNumbers));
    
    menu();
    
    while (input != "0") {}
    while (checkEnd[0] == 0 || checkEnd[1] == 0 || checkEnd[2] == 0 || checkEnd[3] == 0) {}
    
    for (int i = 0; i < threads.size(); i++)
        threads[i].detach();
    
    cout << "Все числа: " << output << endl;
    cout << "Числа десятого срабатывания: " << outputTen << endl;
    cout << "Числа двадцатого срабатывания: " << outputTwenty << endl;
    
    remove("file1.txt");
    remove("file2.txt");
    system("pause");
    return 0;
}
