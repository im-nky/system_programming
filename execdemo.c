#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc,char argv[])
{
	char *args[]={"./f","Nitin","Kumar","Yadav"};
		
	execvp("./f",argv);
	
	printf("Testing!why this kolaveri di?\n");
	
	return 0;	
}
