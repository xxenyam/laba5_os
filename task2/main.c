#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Структура для зберігання аргументів потокової функції
struct thread_arg {
    char *name;  
    char *str;   
    int num;     
};

// Потокова функція
void *thread_func(void *arg) {
    struct thread_arg *targ = (struct thread_arg *)arg;

    for (int i = 1; i <= targ->num; i++) {
        printf("Thread %s. %s %d\n", targ->name, targ->str, i);
        sleep(1); 
    }

    return NULL;
}

int main() {
    pthread_t threads[4];              // Ідентифікатори потоків
    struct thread_arg args[4];          // Масив структур для кожного потоку
    int result;

    // Ініціалізація аргументів для кожного потоку
    args[0].name = "Thread1";
    args[0].str = "Str";
    args[0].num = 4;

    args[1].name = "Thread2";
    args[1].str = "Str";
    args[1].num = 5;

    args[2].name = "Thread3";
    args[2].str = "Str";
    args[2].num =6;

    args[3].name = "Thread4";
    args[3].str = "Str";
    args[3].num = 3;

    // Створення потоків
    for (int i = 0; i < 4; i++) {
        result = pthread_create(&threads[i], NULL, thread_func, &args[i]);
        if (result != 0) {
            fprintf(stderr, "Error creating thread %d\n", i + 1);
            return 1;
        }
    }

    // Очікування завершення всіх потоків
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
