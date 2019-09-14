#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>

void main(){
	int i,j;
	int *bal;
	pid_t pid;
	pid_t ppid = getpid();
	key_t key;
	int shmid;
	sem_t *sem;
	
	key = ftok("/home/user/Documents",3);
	shmid = shmget(key, sizeof(int), 0644 | IPC_CREAT);
	bal = (int *)shmat(shmid, NULL, 0);
	*bal = 1000;
	
	sem = sem_open("sem1", O_CREAT|O_EXCL, 0644, 1);
	
	for(i = 0; i < 2; i++)
		pid = fork();
		
	if(getpid() == ppid + 1){
	    for(j = 0; j < 5; j++){
			sem_wait(sem);
			sleep(2);
			*bal = *bal + 200;
			printf("This is process A. The new balance is : %d\n",*bal);
			sem_post(sem);
		}
	}
	else if(getpid() == ppid + 2){
	    for(j = 0; j < 5; j++){
			sem_wait(sem);
			sleep(2);
			*bal = *bal + 100;
			printf("This is process B. The new balance is : %d\n",*bal);
			sem_post(sem);
		}
	}
	else{
	    while(pid = waitpid(-1, NULL, 0))
			if(errno == ECHILD)
				break;
		shmdt(bal);
		shmctl(shmid, IPC_RMID, 0);
		sem_unlink("sem1");
		sem_close(sem);
	}
}

