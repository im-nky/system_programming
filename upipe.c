#include<stdio.h>
#include<unistd.h>

int main()
{ 
	int pfd[2];
	char buffer[15];
	int pid;
	
	pipe(pfd);
	
	pid=fork();
	
	if(pid>0)
	{
		fflush(stdin);
		printf("\nI'm parent process\n");		
		write(pfd[1],"Hell_world",15);	
	}
	if(pid==0)
	{
		sleep(3);
		fflush(stdin);
		printf("\n I'm child process\n");
		read(pfd[0],buffer,sizeof(buffer));
		//write(1,buffer,sizeof(buffer));		//try with printf
		printf("Msge is %s",buffer);
	}
	return 0;
}
