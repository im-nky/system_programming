#include<stdio.h>
#include<pthread.h>
#define not 2
pthread_t th[not];

int coin_flip=100;

pthread_mutex_t flip_done;

static void *th1(void *_)
{
	pthread_mutex_lock(&flip_done);
	for(int i=0;i<50;i++)
	{
		coin_flip=coin_flip-1;
		printf("\nth1 : flipped coin -%d ",coin_flip);			
	}
	//pthread_mutex_unlock(&flip_done);	
}

static void *th2(void *_)
{
	//pthread_mutex_lock(&flip_done);
	for(int j=0;j<50;j++)
	{
		coin_flip=coin_flip-2;
		printf("\nth2 : flipped coin --%d ",coin_flip);			
	}
	pthread_mutex_unlock(&flip_done);	
}

int main()
{
	pthread_mutex_init(&flip_done,NULL);
	pthread_mutex_lock(&flip_done);
	pthread_create(&th[1],NULL,th1,NULL);
	pthread_create(&th[2],NULL,th2,NULL);
	pthread_mutex_destroy(&flip_done);
	
	pthread_exit(NULL);	
}
