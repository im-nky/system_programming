#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc,char *argv[])
{
	printf("Hello Exec.c");	
	printf("My process id is %d\n",getpid());
	
	printf("My arguments are:\n");
	for(int i=0;i<argc;i++)
	{
		printf("%s",argv[i]);	
	}
	return 0;		
}
