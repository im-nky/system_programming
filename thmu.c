#include<stdio.h> 
#include<pthread.h> 
#include<unistd.h> 

pthread_mutex_t lock;   //declare the mutex lock 
pthread_t tid1, tid2;   //declare thread id variables 
int thread=0;   //declare a counter to 0 to increment in the critical section 

void* func(void* arg) 
{ 
    pthread_mutex_lock(&lock);  //lock the mutex 
    thread++;   //increment thread variable 
    printf("Thread #%d started\n", thread); //print the current thread value 
    sleep(3);   //sleep for 3 seconds 
    printf("Thread #%d finished\n", thread);//print the completed thread value 
    pthread_mutex_unlock(&lock);    //unlock when all the computation for a thread is finished 
    pthread_exit(NULL); //exit thread function 
} 

int main() 
{ 
    pthread_mutex_init(&lock, NULL);    //initialize the mutex lock variable 

    pthread_create(&tid1, NULL, func, NULL);    //create a thread with thread ID = tid1 
    pthread_create(&tid2, NULL, func, NULL);    //createa anothread thread with ID = tid2 

    pthread_join(tid1, NULL);   //wait thread1 to complete 
    pthread_join(tid2, NULL);   //wait thread2 to complete 
    pthread_mutex_destroy(&lock);   //destroy the thread 

    return 0; 
}
