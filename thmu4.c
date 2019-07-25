#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* fun(void* arg)			// thread function should always bbefore main thread
{
	int *i;
	 i=(int *)arg;
	printf("\nHell thread %d \n",*i);
	return NULL;
}

int main()
{
	pthread_t th;
	int x=100;
	int *p=&x;
	printf("\nMAIN THREAD\n");
	//pthread_create(&tid1, NULL, func, NULL); 
	pthread_create(&th,NULL,&fun,(void *)p);
	pthread_join(th,NULL);
	pthread_exit(0);
	return 0;
}


