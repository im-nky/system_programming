#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

int n = 0;
sem_t s;

void* odd_print(void *arg)
{
	while (n < 10)
	{
		sem_wait(&s);
		if(n%2 ==  1 && (n < 10))
		{
			printf("ODD PRINT:%d\n", n);
			n++;
		}
		sem_post(&s);
	}
}

void* even_print(void *arg)
{
	while (n < 10)
	{
		sem_wait(&s);
		if(n%2 == 0 && (n < 10))
		{
			printf("EVEN PRINT:%d\n", n);
			n++;
		}
		sem_post(&s);
	}
}

int main(void)
{
	pthread_t t1, t2;

	if ( sem_init(&s, 0, 1) != 0 )
	{
	     printf("sem_init failed\n");
	}

	pthread_create(&t1, NULL, &even_print, NULL);
	pthread_create(&t2, NULL, &odd_print, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);	

	return 0;
}
