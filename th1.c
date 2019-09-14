// Thread and Signal

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void myhandle(int sigid)
{
	printf("\ngot the signal boss %d",sigid);
	//signal(SIGINT,SIG_DFL);		// Can be used here as well as in main() function
}
// Signal()-can handle 1 signal at a time
// Sigactiion()- for multiple signals
int main()
{
	int i=0;	
	signal(SIGINT,myhandle);	// signal intrrupt by ctrl+C   //SIG_IGN for Ignoring  
	signal(SIGQUIT,myhandle);	// // ctrl+\	//SIG_DFL for default 	//user define handle
	signal(SIGHUP,myhandle);		
	while(1)
	{
		printf("i=%d\n",i++);
		sleep(1);	
	}
	return 1;	
	// kill -l		list all the signal with their id
	
	// from other terminal and kill process id and use ./m format to identify that process 
	// ps -l	not list all the function
	// ps aux	list all the current process
	// kill -9(all process) -1(restart)	kill all the process foreground and background
	//kill -l 11(to find alphabatic name of 11 )
}
