#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void myhandle(int sigid)
{
	printf("\ngot the signal boss %d \n",sigid);
	(void)signal(SIGINT,SIG_DFL);		// Can be used here as well as in main() function
}

// Signal()-can handle 1 signal at a time
// Sigactiion()- for multiple signals

int main()
{
	int i=0;	
	(void)signal(SIGINT,myhandle);	// signal intrrupt by ctrl+C   //SIG_IGN for Ignoring  
	//signal(SIGQUIT,myhandle);	// // ctrl+\	//SIG_DFL for default 	//user define handle
	//signal(SIGHUP,myhandle);		
	while(1)
	{
		printf("\nHell World \n");
		sleep(1);	
	}
	return 1;
}
