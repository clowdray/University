/*
*  prob-1-message.c  (Problem 1a + Problem 1c)
*  Miquel Giné
*  
*  - Create a message queue in a running process
*  - Get data from (prob-1-projection.c) and display output
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
typedef struct application {
	char name[20];
	char customer[20];
	char users[20];
	char turnover[20];
	char CRM[1];
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
int plan_nums = 4; // change to insert more plans
typedef enum {false, true} bool;

/* ------- GLOBAL FUNCTION DECLARATION -------- */
int displayMenu();
void LetsContinue();
void errorOption(int type);
void createFile(int plan_nums);
void sendPetition(int msq_id, request my_request, int data_size);
void readRequest(int msq_id, int data_size);
 
/* ------------------- MAIN ------------------- */
int main(void)
{
	struct request my_request;
	struct answer my_answer;
	
	// gets the MSQ internal id
	if ((msq_id = msgget((key_t)KEY, 0)) == -1)
	{
		perror("msgget");
		exit(1);
	}
	
	bool exitApp = false;
	
	do
	{	
		system("clear");	
		
		switch ( displayMenu() )
		{
			case 0:
				exitApp = true;
				break;
			case 1:				
				createFile(plan_nums);
				
				break;
			case 2:
				if (access("MyPain_plans.txt", F_OK ) != 0) 
				{
					errorOption(1);
				}
				else 
				{	
					sendPetition(msq_id, my_request, plan_nums);
					
					readRequest(msq_id, plan_nums);
				}
				
				break;			
			default:
				errorOption(0);
		}
		
	} while (!exitApp);

	
	exit(0);
}

/* ----------------- FUNCTIONS ---------------- */
int displayMenu()
{
	int inputMenu;

	printf("+------------------------------------------+\n");
	printf("|---------------MyPain-PLANS---------------|\n");
	printf("+------------------------------------------+\n");
	printf("|                                          |\n");
	printf("|- 1 : Write new PLANS  -------------------|\n");
	printf("|- 2 : Read existing PLANS  ---------------|\n");
	printf("|                                          |\n");
	printf("|- 0 : Exit menu  -------------------------|\n");
	printf("|                                          |\n");
	printf("+------------------------------------------+\n\n");
	printf("_- ");
	scanf("%d", &inputMenu);
	
	return inputMenu;
}

void LetsContinue()
{
	printf("\nPress enter Key to Continue\n");  
	getchar();getchar();
	system("clear");
}

void errorOption(int type)
{
	switch (type)
	{
		case 1:
			printf("No plans created yet.\n");
			LetsContinue();
			break;
		case 2:
			printf("\n Value must be [y/n], retry...\n");
			break;
		default:
			printf("No valid option\n");
			LetsContinue();
	}
}

void createFile(int plan_nums)
{
	int fd, i;
	struct application *my_plan;
	
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	fd = open (strcat(cwd, "/MyPain_plans.txt"), O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
	if (fd == -1)
		perror("Error: open file");
	else
	{
		i = 0;
		while (i < plan_nums)
		{
			my_plan = ( struct application* ) malloc (sizeof *my_plan);
			
			printf(" Enter a name: ");
			scanf("%s", my_plan->name);
			printf(" Enter number of customers: ");
			scanf("%s", my_plan->customer);
			printf(" Enter the number of users: ");
			scanf("%s", my_plan->users);
			printf(" Enter the revenue: ");
			scanf("%s", my_plan->turnover);
			
			do
			{
				printf(" Does have CRM [y/n] .: ");
				scanf("%s", my_plan->CRM);
				
				if (strcmp("n",my_plan->CRM) != 0 && strcmp("y",my_plan->CRM) != 0) errorOption(2);
				
			} while(strcmp("n",my_plan->CRM) != 0 && strcmp("y",my_plan->CRM) != 0);
			
			write(fd, my_plan, sizeof *my_plan);
			i++;
			
			if (i < plan_nums) printf("\n=====================================\n\n");
			
			free(my_plan);
		}
		close(fd);
	}
}

void sendPetition(int msq_id, request my_request, int data_size)
{
	my_request.type = 100;
	my_request.data_size = data_size;
	my_request.pid = getpid();
	
	if (msgsnd(msq_id, &my_request, sizeof(struct request), 0) == -1)
	{
		perror("msgsnd");
		exit(4);
	}
}

void readRequest(int msq_id, int data_size)
{
	struct application *my_plan_list;
	struct answer my_answer;
	
	
	int i = 1;
	bool endRead = false;
	while(!endRead) // busy waiting
	{ 
		// read the answer of type 1 with no options
		if (msgrcv(msq_id, &my_answer, sizeof(struct answer), 1, 0) == -1)
		{
			perror("msgrcv");
			exit(2);
		}
		else
		{
			my_plan_list = &my_answer.list_node;

			// printing product database in memory
			printf("%d. plan %s: " 
			"cust[%s], "
			"users[%s], "
			"turn[%s], "
			"CRM[%s] \n", 
			i, 
			my_plan_list->name, 
			my_plan_list->customer, 
			my_plan_list->users, 
			my_plan_list->turnover, 
			my_plan_list->CRM);
			
			i = i + 1;			
		}
		
		if (i > data_size){
			endRead = true;	
		}		
	}
	
	LetsContinue();
}






