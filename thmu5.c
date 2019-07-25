#include<pthread.h>
#include<stdio.h>

pthread_mutex_t lock;

static void *fun()
{
		
}

int main()
{
	pthread_t th;
	pthread_mutex_init(&lock,NULL);
	pthread_create(&th,NULL,fun,NULL);
	pthread_mutex_lock(&lock);
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
	pthread_join(th,NULL);
	pthread_exit(NULL);	
}
