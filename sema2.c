#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define N 10
#define FILE_MODE 0644

struct {
    char buff[3000];
    int nput;
    sem_t *mutex, *nempty, *nfull;
}shared = {
    0, 0
};

void *produce(void *t){
    int num = *(int *)t;
    int i;
    for(i = 0;i < N;i++){
        
        sem_wait(shared.nempty);
        sem_wait(shared.mutex);
        
        shared.buff[shared.nput] = 'x';
        shared.nput++;
        printf("Producer %d: %s\n", num, shared.buff);
        
        sem_post(shared.mutex);
        sem_post(shared.nfull);
        
        sleep(1);
    }
}
void *consume(void *t){
    int num = *(int *)t;
    int i;
    for(i = 0;i < N;i++){
    
        sem_wait(shared.nfull);
        sem_wait(shared.mutex);
       
        shared.nput--;
        shared.buff[shared.nput] = '\0';
        
        printf("Consumer %d: %s\n", num, shared.buff);
        
        sem_post(shared.mutex);
        sem_post(shared.nempty);
        sleep(1);
    }
}

void main(){
    int i,j;
    pthread_t tid_prod[4];
    pthread_t tid_cons[4];
    shared.mutex = sem_open("mutex", O_CREAT | O_EXCL, FILE_MODE, 1);
    shared.nempty = sem_open("nempty", O_CREAT | O_EXCL, FILE_MODE, 10);
    shared.nfull = sem_open("nfull", O_CREAT | O_EXCL, FILE_MODE, 0);
    
    for(i = 0; i < 4;i++){
    
    pthread_create(&tid_prod[i], NULL, produce, (void *)&i);
    pthread_create(&tid_cons[i], NULL, consume, (void *)&i);
    
    }
    for(i = 0; i < 4;i++){
    pthread_join(tid_prod[i], NULL);
    pthread_join(tid_cons[i], NULL);
    }
    
    sem_close(shared.mutex);
    sem_close(shared.nempty);
    sem_close(shared.nfull);
    sem_unlink("mutex");
    sem_unlink("nempty");
    sem_unlink("nfull");
    exit(0);
}
