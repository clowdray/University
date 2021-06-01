/*
*  prob-1-projection.c  (Problem 1b + Problem 1c)
*  Miquel Giné
*  
*  - Projects a file into memory
*  - prints it in a linked list
*
*/

#include <stdio.h>		/* printf */
#include <string.h>		/* strcat */
#include <unistd.h>		/* close */
#include <stdlib.h>		/* malloc */
#include <limits.h>		/* PATH_MAX */
#include <sys/msg.h>		/* msq system calls*/ 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#define KEY 800

/* -------------- GLOBAL STRUCTS -------------- */
typedef struct application{
	char name[20];
	char customer[20];
	char users[20];
	char turnover[20];
	char CRM[5];
	struct application *next;
} application;

typedef struct request {
	long type;
	int data_size;
	pid_t pid;
} request;

typedef struct answer {
	long type;
	application list_node;
	pid_t pid;
} answer;

/* ------------- GLOBAL VARIABLES ------------- */
int msq_id;

/* ------- GLOBAL FUNCTION DECLARATION -------- */
void populateFile(int msq_id, int data_size);


/* ------------------- MAIN ------------------- */
int main(void)
{
	struct request my_request;
	
	// message queue creation
	if ((msq_id = msgget((key_t)KEY, 0750|IPC_CREAT|IPC_EXCL)) == -1)
	{
		perror("msgget");
		exit(1);
	}
	
	while(1)
	{
		if (msgrcv(msq_id, &my_request, sizeof(struct request), 100, MSG_NOERROR) == -1)
		{
			perror("msgrcv");
			exit(2);
		}
		else
		{
			printf("[%ld] Populate file with plans\n", my_request.type);
			populateFile(msq_id, my_request.data_size);
		}
	}
	
	exit(0);
}

/* ----------------- FUNCTIONS ---------------- */
void populateFile(int msq_id, int data_size)
{
	int fd, i, j;
	struct application *my_plan, *current_plan, *my_plan_list;
	struct answer my_answer;
	char *mem_address;
	
	// creates projection
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	fd = open (strcat(cwd, "/MyPain_plans.txt"), O_RDWR);
	if (fd == -1) perror("Error: openfile");
	
	
	size_t my_plan_size = sizeof *my_plan;
	off_t offset = 0;
	
	mem_address = (char*) mmap(NULL, my_plan_size, PROT_READ, MAP_SHARED, fd, offset);

	close(fd);
  
	
	//Creating linked list
	current_plan = NULL; i = 0; j = 0;
	while (i < data_size * sizeof *my_plan)
	{
		my_plan = malloc(sizeof *my_plan);
		
		while (j < sizeof(my_plan->name)) { 	my_plan->name[j] = mem_address[i]; 	i++; j++; } j=0;
    		    		
		while (j < sizeof(my_plan->customer)) { 	my_plan->customer[j] = mem_address[i]; 	i++; j++; } j=0;
				
		while (j < sizeof(my_plan->users)) { 	my_plan->users[j] = mem_address[i]; 	i++; j++; } j=0;
				
		while (j < sizeof(my_plan->turnover)) { 	my_plan->turnover[j] = mem_address[i]; 	i++; j++; } j=0;
				
		while (j < sizeof(my_plan->CRM)) { 	my_plan->CRM[j] = mem_address[i]; 	i++; j++; } j=0;
		
		while (j < ((sizeof *my_plan) - sizeof(my_plan->name)  //get size of pointer to next node
				- sizeof(my_plan->customer) - sizeof(my_plan->users) 
				- sizeof(my_plan->turnover) - sizeof(my_plan->CRM))) { i++; j++; } j=0;
    
		if (current_plan == NULL) //first link
		{ 
			current_plan = my_plan;
			my_plan_list = my_plan; // save first link address
		}
		else
		{
			my_plan->next = NULL;
			current_plan->next = my_plan;
			current_plan = my_plan;
		}
	}
	
	munmap(mem_address, my_plan_size);
	
	while (my_plan_list != NULL)
	{
		//prepares the message and send the answer
		my_answer.type = 1;
		my_answer.list_node = *my_plan_list;
		my_answer.pid = getpid();
		
		if (msgsnd(msq_id, &my_answer, sizeof(struct answer), 0) == -1) {
			perror("msgsnd (answer)");
			exit(3);
		}
		
		my_plan_list = my_plan_list->next;
	}
}





