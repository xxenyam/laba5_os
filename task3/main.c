#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

struct thread_arg {
    char *str;
    int repeat_count;
    int rand_min;
    int rand_max;
    int stop_value;
};

// Функція для потоку, що виводить рядок задану кількість разів
void *print_str(void *arg) {
    struct thread_arg *targ = (struct thread_arg *)arg;

    for (int i = 0; i < targ->repeat_count; i++) {
        fprintf(stderr, "Thread: %s. Str %d\n", targ->str, i + 1);
        sleep(1);
    }

    return NULL;
}

// Функція для потоку, що генерує випадкові числа
void *generate_random(void *arg) {
    struct thread_arg *targ = (struct thread_arg *)arg;
    srand(time(NULL));

    for (int i = 0; i < targ->repeat_count; i++) {
        int rand_num = targ->rand_min + rand() % (targ->rand_max - targ->rand_min + 1);
        fprintf(stderr, "Thread: %s. Random number: %d\n", targ->str, rand_num);

        if (rand_num == targ->stop_value) {
            fprintf(stderr, "Thread: %s. Stop value %d reached. Exiting...\n", targ->str, targ->stop_value);
            return NULL;
        }

        sleep(1);
    }

    return NULL;
}

int main(void) {
    pthread_t thread1, thread2;
    struct thread_arg targ1 = {"Thread1", 6, 0, 0, 0}; 
    struct thread_arg targ2 = {"Thread2", 10, 20, 100, 35}; 

    // Створення першого потоку
    if (pthread_create(&thread1, NULL, &print_str, &targ1) != 0) {
        fprintf(stderr, "Error creating thread1\n");
        return 1;
    }

    // Створення другого потоку
    if (pthread_create(&thread2, NULL, &generate_random, &targ2) != 0) {
        fprintf(stderr, "Error creating thread2\n");
        return 1;
    }

    // завершення обох потоків
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    fprintf(stderr, "All threads have finished. Main thread exiting...\n");

    return 0;
}
