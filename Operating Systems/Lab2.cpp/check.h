using namespace std;

fstream journal; // переменная для работы с журналом
vector<string> journalStrings; // вектор со строками журнала

// функция проверки существования файла
bool fileExists(const char *fname) {
    return access(fname, 0) != -1;
}

// функция создания файла
void createFile(string filename) {
    
    fstream file;
    
    file.open(filename + ".txt", ios::out);
    file.close();
}

// функция удаления файла
void deleteFile(string filename) {
    string delFilename;
    delFilename = filename + ".txt";
    remove(delFilename.c_str());
}

// функция изменения файла
void modifyFile(string& filename) {
    fstream file;
    string data;
    
    file.open(filename + ".txt", ios::out | ios::app);
    
    cout << "Введите данные: ";
    cin >> data;
    file << data << endl;
    
    file.close();
}

// функция поиска файла
string findName(string str) {
    int index = str.find_first_of(']');
    return str.substr(1, index - 4);
}

// функция коррекции журнала
void fixFile(string file, string code) {
    if (code == "100") {
        cout << "Файл " + file + " был создан." << endl;
        journalStrings.push_back("[" + file + "100] Файл " + file + " создаётся.");
        createFile ("/Users/hollo/Library/Developer/Xcode/DerivedData/Lab2-fhwgnvedsksejudrmclqovarmgtg/Build/Products/Debug" + file + ".txt");
        journalStrings.push_back("[" + file + "000] Файл " + file + " создан.\n");
    }
    else {
        if (code == "010") {
            int answer;
            journalStrings.push_back("[" + file + "010] Файл " + file + " не закончил изменение."); //добавил в лог
            cout << "Файл " + file + " не закончил изменение. Оставить файл(0) или удалить(1): ";
            cin >> answer;
            if (answer == 0) {
                journalStrings.push_back("[" + file + "010] Файл " + file + " изменяется.");
                journalStrings.push_back("[" + file + "000] Файл " + file + " изменен.");
                return;
            }
        }
        else
            cout << "Файл " + file + " был удалён." << endl;
        journalStrings.push_back("[" + file + "001] Файл " + file + " удаляется.");
        deleteFile("/Users/hollo/Library/Developer/Xcode/DerivedData/Lab2-fhwgnvedsksejudrmclqovarmgtg/Build/Products/Debug" + file + ".txt");
        journalStrings.push_back("[" + file + "000] Файл " + file + " удалён.");
    }
}

void checkingJournal() {
    string str;
    
    journal.open("/Users/hollo/Library/Developer/Xcode/DerivedData/Lab2-fhwgnvedsksejudrmclqovarmgtg/Build/Products/Debug/log.txt", ios::in);
    
    while (!journal.eof()) {
        getline(journal, str, '\n');
        if (str != "")
            journalStrings.push_back(str);
    }
    
    journal.close();
    
    for (int i = 1; i < 11; i++) {
        int savedIndex = -1;
        int previousIndex = savedIndex;
        int checkError = 0;
        string code;
        stringstream sstr;
        string filename;
        sstr << i;
        sstr >> filename;
        
        for (int j = 0; j < journalStrings.size();) {
            if (findName(journalStrings[j]) == filename) {
                if (checkError == 0) {
                    code = journalStrings[j].substr(2, 3);
                    
                    if (code != "000")
                        //Если код предыдущей записи не равен 000, выполняется удаления удаление всех следующих записей
                        if ((savedIndex != -1 && journalStrings[savedIndex].substr(2, 3) != "000")) {
                            checkError = 1;
                            code = journalStrings[savedIndex].substr(2, 3);
                            journalStrings.erase(journalStrings.begin() + savedIndex);
                            j--;
                        }
                    
                    previousIndex = savedIndex;
                    savedIndex = j;
                    if (checkError == 0)
                        j++;
                }
                else {
                    journalStrings.erase(journalStrings.begin() + j);
                }
            }
            else {
                j++;
            }
        }
        
        // если обнаружена ошибка — журнал исправляется
        if (checkError == 1)
            fixFile(filename, code);
        
        // проверка наличия файла
        if (savedIndex != -1 && checkError == 0) {
            if (code != "000") {
                fixFile(filename, code);
                journalStrings.erase(journalStrings.begin() + savedIndex);
                checkError = 1;
            }
            else {
                if (previousIndex == -1)
                    previousIndex = savedIndex;
                string status = journalStrings[previousIndex].substr(2, 3);
                if ((status == "100" || status == "010") && !fileExists(("/Users/hollo/Library/Developer/Xcode/DerivedData/Lab2-fhwgnvedsksejudrmclqovarmgtg/Build/Products/Debug/" + filename + ".txt").c_str())) {
                    
                    journalStrings.push_back("[" + filename + "000] Файл " + filename + " удалён.");
                    cout << "Записи в журнале для файла " + filename + " скорректированы." << endl;
                }
                else
                    if (status == "001" && fileExists(("/Users/hollo/Library/Developer/Xcode/DerivedData/Lab2-fhwgnvedsksejudrmclqovarmgtg/Build/Products/Debug/" + filename + ".txt").c_str())) {
                        
                        int answer;
                        
                        cout << "Файл " + filename + " создан вручную - удалить(1) или оставить файл(0): ";
                        cin >> answer;
                        if (answer == 0) {
                            journalStrings.push_back("[" + filename + "000] Файл " + filename + " создан.");
                            cout << "Файл " + filename + " создан." << endl;
                        }
                        else {
                            remove(("/Users/hollo/Library/Developer/Xcode/DerivedData/Lab2-fhwgnvedsksejudrmclqovarmgtg/Build/Products/Debug/" + filename + ".txt").c_str());
                            cout << "Файл " + filename + " удалён." << endl;
                        }
                    }
            }
        }
        else
            // если записей о файле нет, но он создан
            if (savedIndex == -1 && fileExists(("/Users/hollo/Library/Developer/Xcode/DerivedData/Lab2-fhwgnvedsksejudrmclqovarmgtg/Build/Products/Debug" + filename + ".txt").c_str())) {
                
                int answer;
                
                cout << "Файл " + filename + " создан вручную - удалить(1) или оставить файл(0): ";
                cin >> answer;
                if (answer == 0) {
                    journalStrings.push_back("[" + filename + "000] Файл " + filename + " создан.");
                    cout << "Файл " + filename + " создан." << endl;
                }
                else {
                    remove(("/Users/hollo/Library/Developer/Xcode/DerivedData/Lab2-fhwgnvedsksejudrmclqovarmgtg/Build/Products/Debug/" + filename + ".txt").c_str());
                    cout << "Файл " + filename + " удалён." << endl;
                }
            }
    }
    
    journal.open("/Users/hollo/Library/Developer/Xcode/DerivedData/Lab2-fhwgnvedsksejudrmclqovarmgtg/Build/Products/Debug/log.txt", ios::out | ios::trunc);
    
    for (int i = 0; i < journalStrings.size(); i++)
        journal << journalStrings[i] << endl;
    
    journal.close();
}

void hi() {
    cout << "hi" << endl;
}

