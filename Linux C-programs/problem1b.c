/*
*  Problema1b.c
*  Miquel Giné
*  - fork
*  - fork
*    - fork
*  - fork
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
    	int gen1 = 3;
    	int gen2 = 1;
    	    	    	    	
	for (int i = 0; i < gen1; i++)
	{						
		if (pid > 0 && i == 0)
		{
			printf("PID.origin [ %d ]\n\n", getpid());
		}		
		
		if (pid == 0 && i == 1)
		{
			for (int k = 0; k < gen2; k++)
			{
				pid = fork();
				
				if (pid == 0) 
				{
					proccessPrint(i+10+k,2);
					killProccess();
				}				
			}
			
			if (pid > 0)
			{
				proccessPrint(i,1);
				for (int n = 0; n<gen2; n++) wait(0);
				killProccess();
			}
		}
		else if (pid == 0)
		{
			proccessPrint(i,1);
			if (i == 2)
			{
				sleep(10);
				printf("\nis orphan -->  ");
				proccessPrint(i,1);
			}
			killProccess();
			printf("\n");
		}
		
		if (pid > 0 && i < gen1-1)
		{
			pid = fork();			
		}			
	}
	
	if (pid > 0)
	{
		for (int n = 0; n<gen1-1; n++) wait(0);
		killProccess();		
	}
	        
    	return 0;
}



