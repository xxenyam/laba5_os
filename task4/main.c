#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

unsigned long long *catalanNumbers; 
int catalanCount;

// Функція для обчислення чисел Каталана
void *calculate_catalan(void *arg) {
    int n = catalanCount;
    catalanNumbers = malloc(n * sizeof(unsigned long long));
    if (catalanNumbers == NULL) {
        perror("Не вдалося виділити пам'ять");
        exit(EXIT_FAILURE);
    }

    catalanNumbers[0] = 1;
    for (int i = 1; i < n; i++) {
        catalanNumbers[i] = 0;
        for (int j = 0; j < i; j++) {
            catalanNumbers[i] += catalanNumbers[j] * catalanNumbers[i - j - 1];
        }
    }
    return NULL;
}

// Функція для обчислення простих чисел
void *calculate_primes(void *arg) {
    int count = *(int *)arg;
    printf("Прості числа:\n");
    int num = 2; 
    int found = 0;

    while (found < count) {
        int is_prime = 1; 
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                is_prime = 0; 
                break;
            }
        }
        if (is_prime) {
            printf("%d ", num);
            found++;
        }
        num++;
    }
    printf("\n");
    return NULL;
}

int main() {
    printf("Введіть кількість чисел Каталана: ");
    scanf("%d", &catalanCount);
    
    int primeCount;
    printf("Введіть кількість простих чисел: ");
    scanf("%d", &primeCount);

    pthread_t thread1, thread2;

    // Створюємо потік для обчислення чисел Каталана
    if (pthread_create(&thread1, NULL, calculate_catalan, NULL) != 0) {
        perror("Не вдалося створити потік для чисел Каталана");
        return EXIT_FAILURE;
    }

    // Створюємо потік для обчислення простих чисел
    if (pthread_create(&thread2, NULL, calculate_primes, &primeCount) != 0) {
        perror("Не вдалося створити потік для простих чисел");
        return EXIT_FAILURE;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Числа Каталана:\n");
    for (int i = 0; i < catalanCount; i++) {
        printf("%llu ", catalanNumbers[i]); 
    }
    printf("\n");

    free(catalanNumbers);

    return 0;
}






