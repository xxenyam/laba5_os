#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h> 

// Функція нового потоку
void *child_thread_func(void *args) {
    for (int i = 1; i <= 10; i++) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3); 
    }
    return NULL;
}

int main() {
    pthread_t thread;
    int result;
// Створення нового потоку
    result = pthread_create(&thread, NULL, child_thread_func, NULL);
    if (result != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

// Головний потік
    for (int i = 1; i <= 10; i++) {
        printf("Main Thread. Iteration: %d\n", i);
        sleep(rand() % 3); 
    }

    pthread_join(thread, NULL);
    return 0;
}

