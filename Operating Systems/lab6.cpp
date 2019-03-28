#include <stdlib.h> // выделение памяти С
#include <stdio.h> // ввод-вывод для C
#include <pthread.h> // POSIX потоки
#include <sched.h> // библиотека для планирования
#include <unistd.h> // POSIX примитивы для взаимодействия с ОС
#include <math.h>

// дадим идентификатор кол-ву потоков
#define numberOfThread 4

pthread_mutex_t consoleMutex;
pthread_mutex_t mutedThread[numberOfThread];
pthread_t threads[numberOfThread];
pthread_cond_t lock[numberOfThread];

int started [] = { 1,1,1,1 };
int stopped [] = { 0,0,0,0 };
int checkEnd [] = { 1,1,1,1 };

struct threadInfo {
    int id;
    int priority;
};

struct threadInfo statuses[numberOfThread];

int factorial(int i) {
    if (i==0) return 1;
    else return i*factorial(i-1);
}

void *threadFunction(void *arg) {
    struct threadInfo *info = (struct threadInfo *)arg;
    while (true){
        if (started[info->id] == 1) {
            sleep(1);
            switch (info->id) {
                case 0: {
                    int res = factorial(6);
                    break;
                }
                case 1: {
                    float res = factorial(4);
                    break;
                }
                case 2: {
                    float res = factorial(9);
                    break;
                }
                case 3: {
                    int res = factorial(5);
                    break;
                }
                default: {
                    break;
                }
            }
            
            pthread_mutex_lock(&consoleMutex);
            printf("Thread %d with priotity %d stoped\n", (info->id + 1), info->priority);
            pthread_mutex_unlock(&consoleMutex);
            started[info->id]--;
            
            pthread_mutex_lock(&mutedThread[info->id]);
            pthread_cond_wait(&lock[info->id], &mutedThread[info->id]);
            pthread_mutex_unlock(&mutedThread[info->id]);
        }
        else {
            checkEnd[info->id]--;
            stopped[info->id]++;
            pthread_exit(0);
        }
    }
}

void menu () {
    printf("\nRestart - 1. Exit - 0:\n");
}

int main()
{
    srand((unsigned int)time(0));
    int check;
    
    // мьютекс для вывода в консоль
    pthread_mutex_init(&consoleMutex, NULL);
    
    // мютекс для потоков
    for (int i = 0; i < numberOfThread; i++)
        pthread_mutex_init(&mutedThread[i], NULL);

    for (int i = 0; i < numberOfThread; i++)
        pthread_cond_init(&lock[i], NULL);
    
    for (int i = 0; i < numberOfThread; i++) {
        // заполняем информационную структуру потоков
        statuses[i].id = i;
        switch (i) {
            case 0: {
                statuses[i].priority = 10;
                break;
            }
            case 1: {
                statuses[i].priority = 90;
                break;
            }
            case 2: {
                statuses[i].priority = 40;
                break;
            }
            case 3: {
                statuses[i].priority = 70;
                break;
            }
            default: {
                break;
            }
        }
        
        int result = pthread_create(&threads[i], NULL, threadFunction, (void *)&statuses[i]);
        
        if (result != 0) {
            pthread_mutex_lock(&consoleMutex);
            printf("Thread can't created. error: %i", result);
            pthread_mutex_unlock(&consoleMutex);
            exit(0);
        }
        
        // выставляем приоритеты на основе данных структуры потока
        pthread_setschedprio(threads[i], statuses[i].priority);
        pthread_mutex_lock(&consoleMutex);
        printf("Thread %d with priority %d started\n", i + 1, statuses[i].priority);
        pthread_mutex_unlock(&consoleMutex);
    }
    
    while ((stopped[0] == 0) || (stopped[1] == 0) || (stopped[2] == 0) || (stopped[3] == 0)) {
        if ((started[0] == 0) && (started[1] == 0) && (started[2] == 0) && (started[3] == 0)) {
            int choice;

            menu();
            do {
                choice = scanf("%d", &check);
                while (getchar() != '\n');
                if (choice != 1)
                    printf("%s", "Error!\n");
                    
            } while (choice != 1);
            
            if (check == 1) {
                for (int i = 0; i < numberOfThread; i++) {
                    started[i]++;
                    pthread_cond_signal(&lock[i]);
                    pthread_mutex_lock(&consoleMutex);
                    printf("Thread %d with priority %d started\n", i + 1, statuses[i].priority);
                    pthread_mutex_unlock(&consoleMutex);
                }
            }
            else {
                for (int i = 0; i < numberOfThread; i++)
                    pthread_cond_signal(&lock[i]);
                int checkFin = numberOfThread;
                while (checkFin > 0) {
                    for (int i = 0; i < numberOfThread; i++) {
                        if (checkEnd[i] == 0) {
                            printf("%s %i %s \n","Thread",(i + 1),"destroyed");
                            checkEnd[i]++;
                            checkFin--;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
