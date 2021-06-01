/*
*  Problema1a.c
*  Miquel Giné
*  - fork
*    -fork
*      -fork
*        -fork
*
*/
#include <stdio.h>      /* stderr, stdout, printf */
#include <unistd.h>     /* fork */
#include <sys/wait.h>   /* wait */
#include <stdlib.h>     /* exit */

void proccessPrint(int i, int level)
{
	for (int k = 0; k<level; k++)
	{
		printf("   ");
	}
	printf("PID.son-%d [ %d ]\n", i+1, getpid());
	
	for (int k = 0; k<level; k++)
	{
		printf("   ");
	}
	printf("PID.father-%d [ %d ]\n\n", i, getppid());
}

void killProccess()
{
	printf("PID [ %d ] is killed.\n", getpid());
	exit(0);
}

int main(void)
{
    	pid_t pid;
    	pid = fork();
    	
	for (int i=0; i<3; i++)
    	{
       	if (pid > 0 && i == 0)
		{
			printf("PID.origin [ %d ]\n\n", getpid());		
		}       	
       	
       	if (pid == 0) 
       	{
       		proccessPrint(i, i+1);
	  
	  		if (i == 2)   //just to see if 4th son is orphan
	  		{
	  			sleep(10);
	  			printf("\n");
	  			proccessPrint(i,i+1);
	  			
	  			killProccess(); 
	  		}
	  		
	  		pid = fork();          
       	}
       	else
       	{
	  		if (i != 2)
	  		{
	     			wait(0);
	     
	     			if (i == 0) i = 3;
	  		}
	  		else sleep(5);
	  
	  		killProccess();
	  		printf("\n");       
		}
	}
    
    
    return 0;
}

