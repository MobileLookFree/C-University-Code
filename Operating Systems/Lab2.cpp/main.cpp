#include <iostream>
//#include <io.h> // access на Windows
//#include <sys/uio.h> // access на macOS - не заработал
#include <unistd.h> // access на Linux
#include <fstream>
#include <string>
#include <sstream> // форматирование строк
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "check.h"

using namespace std;

mutex mutexJornal; // мьютекс для блокировки потока журналирования
mutex mutexFile; // мьютекс для блокировки потока управления файлами
condition_variable cvJornal; // условная переменная для контроля потока журнала
condition_variable cvFile; // условная переменная для контроля потока управления файлами

string selectedFile; // имя выбранного файла
int choice; // пункт меню
int checkEnd; // проверка завершения программы
int fileStatus; // статус операции

// функция журналирования
void journaling() {
    fstream journal;
    
    while (checkEnd == 0) {
        unique_lock<mutex> lockJorn(mutexJornal);
        cvJornal.wait(lockJorn);
        
        journal.open("log.txt", ios::out | ios::app);
        
        switch (choice) {
            case 1: {
                if (fileStatus == 0)
                    journal << "[" << selectedFile << "000] Файл " << selectedFile << " создан.\n";
                else
                    journal << "[" << selectedFile << "100] Файл " << selectedFile << " создаётся.\n";
                break;
            }
            case 2: {
                if (fileStatus == 0)
                    journal << "[" << selectedFile << "000] Файл " << selectedFile << " изменен.\n";
                else
                    journal << "[" << selectedFile << "010] Файл " << selectedFile << " изменяется.\n";
                break;
            }
            case 3: {
                if (fileStatus == 0)
                    journal << "[" << selectedFile << "000] Файл " << selectedFile << " удалён.\n";
                else
                    journal << "[" << selectedFile << "001] Файл " << selectedFile << " удаляется.\n";
                break;
            }
            default:
                break;
        }
        
        journal.close();
        
        cvFile.notify_one();
    }
}

void menu () {
    cout << "Выберите действие:" << endl;
    cout << "1. Создать файл" << endl;
    cout << "2. Записать в файл" << endl;
    cout << "3. Удалить файл" << endl;
    cout << "4. Отмена" << endl;
    cout << "Выбор: ";
}

// функция работы с файлами
void fileWorking() {
    string deletedFile;
    
    while (checkEnd == 0) {
        unique_lock<mutex> lockFile(mutexFile);
        
        cout << "Введите номер файла (1 - 10):";
        cin >> selectedFile;
        
        if (selectedFile == "0") {
            checkEnd = 1;
            return;
        }
        
        do {
            menu();
            cin >> choice;
            
            switch (choice) {
                case 0: {
                    checkEnd = 1;
                }
                case 1: {
                    if (fileExists((selectedFile + ".txt").c_str()))
                        cout << "Файл уже создан!" << endl;
                    else {
                        fileStatus = 1;
                        cvJornal.notify_one();
                        cvFile.wait(lockFile);
                        
                        createFile(selectedFile);
                        
                        fileStatus = 0;
                        cvJornal.notify_one();
                        cvFile.wait(lockFile);
                    }
                    
                    break;
                }
                case 2: {
                    if (fileExists((selectedFile + ".txt").c_str())) {
                        fileStatus = 1;
                        cvJornal.notify_one();
                        cvFile.wait(lockFile);
                        
                        modifyFile(selectedFile);
                        
                        fileStatus = 0;
                        cvJornal.notify_one();
                        cvFile.wait(lockFile);
                    }
                    else {
                        cout << "Файл не создан!" << endl;
                    }
                    break;
                }
                case 3: {
                    if (fileExists((selectedFile + ".txt").c_str())) {
                        fileStatus = 1;
                        cvJornal.notify_one();
                        cvFile.wait(lockFile);
                        
                        deleteFile(selectedFile);
                        
                        fileStatus = 0;
                        cvJornal.notify_one();
                        cvFile.wait(lockFile);
                    }
                    else {
                        cout << "Файл не создан!" << endl;
                    }
                    break;
                }
                case 4: {
                    break;
                }
                default:
                    cout << "Ошибка ввода!" << endl;
                    break;
            }
        } while (choice < 0 || choice > 4);
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    
    vector<thread> threads;
    
    hi();
    cout << "Для завершения введите 0" << endl;
    
    threads.push_back(thread(fileWorking));
    threads.push_back(thread(journaling));
    
    checkingJournal();
    
    while (checkEnd == 0) {}
    
    for (int i = 0; i < threads.size(); i++)
        threads[i].detach();
    
    system("pause");
    return 0;
}

