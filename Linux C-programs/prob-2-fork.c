/*
*  prob-2-fork.c    (Problema 2a)
*  Miquel Giné
*  
*  - create 4 childs who reads variables from father with semaphore
*
*/

#include <stdio.h>		/* stderr, stdout, printf */
#include <unistd.h>		/* fork */
#include <sys/wait.h>		/* wait */
#include <stdlib.h>		/* exit */
#include <semaphore.h>
#include <sys/shm.h>		/* shm system calls*/
#define KEY 256

/* -------------- GLOBAL STRUCTS -------------- */
typedef struct memo {
	int rcount;
	int message;
	int counter;
	sem_t wSem;
	sem_t rSem;
} memo;

/* ------------- GLOBAL VARIABLES ------------- */
int shm_id, semValue = 0;
sem_t writerSemaphore, readerSemaphore;
memo *memory_address;

/* ------- GLOBAL FUNCTION DECLARATION -------- */
void writer();
void reader(int f);

/* ------------------- MAIN ------------------- */
int main()
{
	int pid; // pid5 is for writer
	sem_init(&writerSemaphore,1,1); //second argument has a non-zero value, then the semaphore is shared between processes; 
	sem_init(&readerSemaphore,1,1); //second argument has a non-zero value, then the semaphore is shared between processes;
	
	// process creare a shared memory creation associated to its adress space
	if ((shm_id = shmget((key_t)KEY, 1000, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
		perror("shmget");
		exit(1);
	}
	
	// attachment to current process
	if ((memory_address = shmat(shm_id, NULL, 0)) == (void *)-1)
	{
		perror("shmat");
		exit(2);
	}
	
	memory_address->message = 8000;
	memory_address->rcount = 0;
	memory_address->counter = 0;
	memory_address->wSem = writerSemaphore;
	memory_address->rSem = readerSemaphore;
	
	pid = fork();
	if (pid > 0) {
		pid = fork();
		if (pid > 0) {
			pid = fork();
			if (pid > 0) {
				pid = fork();
				if (pid > 0) {
					pid = fork();
					if (pid > 0) {
						wait(0);
						wait(0);
						wait(0);
						wait(0);
						wait(0);
					} else if (pid == 0) writer();
				} else if (pid == 0) reader(4);
			} else if (pid == 0) reader(3);
		} else if (pid == 0) reader(2);
	} else if (pid == 0) reader(1);
		
	// region destruction
	shmctl(shm_id, IPC_RMID, NULL);
	
	sem_destroy(&writerSemaphore); 
	sem_destroy(&readerSemaphore);
	return 0;
}

/* ----------------- FUNCTIONS ---------------- */
void writer()
{	
	for (int i = 0 ; i<6 ; i++){
		sem_getvalue(&memory_address->wSem, &semValue);
		while (semValue == 0) { sem_getvalue(&memory_address->wSem, &semValue); }
		
		memory_address->counter = 0;
		memory_address->message = memory_address->message + 200;
		printf("WRITER: HTTP-code[%d] PendingRequest[%d]\n", memory_address->message, memory_address->counter);
		
		sem_wait(&memory_address->wSem); //writerSemaphore --> 0			
	}
	
	// region detachment
	if (shmdt(memory_address))
	{
		perror("shmdt");
		exit(3);
	}
}

void reader(int f)
{
	// attachment to current process
	if ((memory_address = shmat(shm_id, NULL, 0)) == (void *)-1)
	{
		perror("shmat");
		exit(2);
	}
	  
	for(int k=0 ; k<6 ; k++){
		sem_getvalue(&memory_address->wSem, &semValue);
		while (semValue == 1) { sem_getvalue(&memory_address->wSem, &semValue); }
		
		sem_wait(&memory_address->rSem);
		
		if((memory_address->rcount = memory_address->rcount + 1) == 1)
		{			
			printf("\n===============================\n");
		}
		
		memory_address->counter = memory_address->counter + 1;
		
		printf("  READER[%d]: HTTP-code[%d] RequestQueued[%d]\n", f, memory_address->message, memory_address->counter);
		
		if(memory_address->rcount == 4)
		{
			memory_address->rcount = 0;
			printf("===============================\n\n");
			
			sem_post(&memory_address->wSem); //writerSemaphore --> 1
		}
		sem_post(&memory_address->rSem);
		sleep(2);
	}
	
	// region detachment
	if (shmdt(memory_address))
	{
		perror("shmdt");
		exit(3);
	}
}





