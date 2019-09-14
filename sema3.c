#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

#define FILE_MODE 0644

struct {
    int measure;
    sem_t *mutex;
}shared = {
    0
};

void *perform(void *t){
    int num = *(int *)t;
    double sleep_prob = 0.25;
    while(shared.measure < 50){   
        sem_wait(shared.mutex);
        double temp = rand() / RAND_MAX + 0.24;
        if(temp < sleep_prob){
            printf("musician %d sleeping\n",num);
            sleep(rand() % 5 + 1);
        }
        else{
            printf("musician %d playing\n",num);
            sleep(1);
        }
        sem_post(shared.mutex);
       
    }
}

void main(){
    int i = 3;
    int j;
    pthread_t tid_musician[3];
    shared.mutex = sem_open("mutex", O_CREAT | O_EXCL, FILE_MODE, 3);
    
    for(i = 0;i < 3; ++i){
        pthread_create(&tid_musician[i], NULL, perform, (void *)&i);
    }
    
    for(j = 0;j < 50; j++){
        printf("Measure %d:\n",shared.measure);
        shared.measure++;
        sleep(1);
    }
    
    for(i = 0; i < 3;i++){
        pthread_join(tid_musician[i], NULL);
    }
    
    sem_close(shared.mutex);
    sem_unlink("mutex");
    exit(0);
}
