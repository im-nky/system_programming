#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
int n=5;
int child(int );

int main()
{
	child(n);
}

int child(int n)
{
	int pid;	
	if(n==0)
	{
		return 0;
	}
	pid=fork();
	if(pid==0)	
	{		
		printf("\nMy Process Id is : %d  \nMy Parent Id is : %d\n\n", getppid(), getpid() );
		child(n-1);			
		exit(0);		// Use Recursion of linearly parent-child printing 
	}
	if(pid>0)
	{
		wait(NULL);
	}
	return 0;
}
