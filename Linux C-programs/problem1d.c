/*
*  Problema1d.d
*  Miquel Giné
*  - fork
*    - fork
*    - fork
*  - fork
*    - fork
*      - fork
*      - fork
*    - fork
*      - fork
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
    	int gen1 = 2;
    	int gen21 = 2;
    	int gen22 = 2;
    	int gen31 = 2;
    	int gen32 = 1;
    	    	    	    	
	for (int i = 0; i < gen1; i++)
	{						
		if (pid > 0 && i == 0)
		{
			printf("PID.origin [ %d ]\n\n", getpid());
		}		
		
		if (pid == 0 && i == 0)
		{
			for (int k = 0; k < gen21; k++)
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
				for (int n = 0; n<gen21; n++) wait(0);
				killProccess();
			}
		}
		if (pid == 0 && i == 1)
		{
			for (int k = 0; k < gen22; k++)
			{
				pid = fork();
				
				if (pid == 0 && k == 0) 
				{
					for (int k = 0; k < gen31; k++)
					{
						pid = fork();
						
						if (pid == 0) 
						{
							proccessPrint(i+10+k,3);
							killProccess();
						}				
					}
					
					if (pid > 0)
					{
						proccessPrint(i,1);
						for (int n = 0; n<gen31; n++) wait(0);
						killProccess();
					}
				}
				if (pid == 0 && k == 1)
				{
					for (int k = 0; k < gen32; k++)
					{
						pid = fork();
						
						if (pid == 0) 
						{
							proccessPrint(i+10+k,3);
							killProccess();
						}				
					}
					
					if (pid > 0)
					{
						proccessPrint(i,1);
						for (int n = 0; n<gen32; n++) wait(0);
						killProccess();
					}
				}				
			}
			
			if (pid > 0)
			{
				proccessPrint(i,1);
				for (int n = 0; n<gen22; n++) wait(0);
				killProccess();
			}
		}
		
		if (pid > 0 && i < gen1-1)
		{
			pid = fork();			
		}
	}
	
	if (pid > 0)
	{
		for (int n = 0; n<gen1; n++) wait(0);
		killProccess();		
	}
	        
    	return 0;
}



