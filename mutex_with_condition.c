#include <stdio.h>
#include <pthread.h>

int n = 0;  
pthread_mutex_t lock;
pthread_cond_t cond_even, cond_odd;
int turn = 0;  // 0 = even thread's turn, 1 = odd thread's turn

void* even_print(void* arg) {
    while (n < 10) {
        pthread_mutex_lock(&lock);

        while (turn != 0) {  // Wait if it's not the even thread's turn
            pthread_cond_wait(&cond_even, &lock);
        }

        if (n >= 10) {
            pthread_mutex_unlock(&lock);
            pthread_cond_signal(&cond_odd);
            break;
        }

        printf("EVEN PRINT: %d\n", n);
        n++;
        turn = 1;  // Now it's the odd thread's turn

        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&cond_odd);  // Wake up the odd thread
    }
    return NULL;
}

void* odd_print(void* arg) {
    while (n < 10) {
        pthread_mutex_lock(&lock);

        while (turn != 1) {  // Wait if it's not the odd thread's turn
            pthread_cond_wait(&cond_odd, &lock);
        }

        if (n >= 10) {
            pthread_mutex_unlock(&lock);
            pthread_cond_signal(&cond_even);
            break;
        }

        printf("ODD PRINT: %d\n", n);
        n++;
        turn = 0;  // Now it's the even thread's turn

        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&cond_even);  // Wake up the even thread
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond_even, NULL);
    pthread_cond_init(&cond_odd, NULL);

    pthread_create(&t1, NULL, even_print, NULL);
    pthread_create(&t2, NULL, odd_print, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond_even);
    pthread_cond_destroy(&cond_odd);

    return 0;
}
