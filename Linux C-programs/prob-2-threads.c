/*
*  prob-2-threads.c  (Problem 2b)
*  Miquel Giné
*  
*  - Main thread writes 6 times and reader reads message and
*    increments the counter. Then server modifies the message
*    and reset counter variable
*
*/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

/* ------------- GLOBAL VARIABLES ------------- */

sem_t writerSemaphore, readerSemaphore;
int counter = 0, message = 8000, rcount = 0, semValue = 0;

/* ------- GLOBAL FUNCTION DECLARATION -------- */
void *reader(void *arg);

/* ------------------- MAIN ------------------- */
int main()
{
	int i; 
	pthread_t rtid[4];
	sem_init(&writerSemaphore,0,1);
	sem_init(&readerSemaphore,0,1);
	for(i=0;i<4;i++)
	{
		pthread_create(&rtid[i],NULL,reader, (void *) i);
	}
  
	for (i = 0 ; i<6 ; i++)
	{
		sem_getvalue(&writerSemaphore, &semValue);
		while (semValue == 0) { sem_getvalue(&writerSemaphore, &semValue); }

		counter = 0;
		message = message + 200;
		printf("WRITER: HTTP-code[%d] PendingRequest[%d]\n", message, counter);
		
		sem_wait(&writerSemaphore); //writerSemaphore --> 0
	}
  
	for(i=0;i<4;i++)
	{
		pthread_join(rtid[i],NULL);
	}
	
	sem_destroy(&writerSemaphore); 
	sem_destroy(&readerSemaphore);
	pthread_exit(NULL);
	return 0;
}

/* ----------------- FUNCTIONS ---------------- */
void *reader(void *arg)
{
	int f,k;
	
	f = (int) arg;
	  
	for(k=0 ; k<6 ; k++){
		sem_getvalue(&writerSemaphore, &semValue);
		while (semValue == 1) { sem_getvalue(&writerSemaphore, &semValue); }
		
		sem_wait(&readerSemaphore);
		
		if((rcount = rcount + 1) == 1)
		{			
			printf("\n===============================\n");
		}
		
		counter = counter + 1;
		
		printf("  READER[%d]: HTTP-code[%d] RequestQueued[%d]\n", f, message, counter);
		
		if(rcount == 4)
		{
			rcount = 0;
			printf("===============================\n\n");
			
			sem_post(&writerSemaphore); //writerSemaphore --> 1
		}
		sem_post(&readerSemaphore);
		sleep(2);
	}
}



