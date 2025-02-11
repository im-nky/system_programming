#include <stdio.h>
#include <pthread.h>

int n = 0;
pthread_mutex_t lock;

void* odd_print(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&lock);
		if (n >= 10) // Exit condition inside the lock
		{
			pthread_mutex_unlock(&lock);
			break;
		}
		if (n % 2 == 1)
		{
			printf("ODD PRINT: %d\n", n);
			n++;
		}
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

void* even_print(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&lock);
		if (n >= 10) // Exit condition inside the lock
		{
			pthread_mutex_unlock(&lock);
			break;
		}
		if (n % 2 == 0)
		{
			printf("EVEN PRINT: %d\n", n);
			n++;
		}
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main(void)
{
	pthread_t t1, t2;

	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("mutex_init failed\n");
		return 1;
	}

	pthread_create(&t1, NULL, &even_print, NULL);
	pthread_create(&t2, NULL, &odd_print, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&lock); // Destroy the mutex after usage

	return 0;
}
