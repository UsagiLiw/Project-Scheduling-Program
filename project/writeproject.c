/***********************************************************
*
* file name : writeproject.c
*	This program receive input 
*	from user and store it by using linkedlist
*
*	Create by : Nonthakorn Sukprom 60070503435
*				Nutchanon Veraphichkasem 60070503422
*
***********************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	char firstName[32];
	char lastName[32];

} NAME_T;

typedef struct _task
{
	char Topic[32];
	char taskDescription[1000];
	int Time;
	NAME_T ** responsMem;
	int memberCount;
    struct _task * nextTask;

} TASK_T;

typedef struct
{
	char projectName[32];
	char description[1000];
	NAME_T * name;
	TASK_T * task;
} PROJECT_T;

typedef struct
{
    TASK_T * head;          /*head of list*/
    TASK_T * tail;          /*tail of list*/
    TASK_T * current;       /*current item in list*/
} LIST_T;

int main()
{
	LIST_T * list = NULL;
	NAME_T * name = NULL;
	TASK_T * task = NULL;
	TASK_T * head = NULL;
	TASK_T * tail = NULL;
	PROJECT_T project;
	char input[256];
	int taskAmount = 0;
	int member = 0;
	int taskMember = 0;
	int i = 0;
	int j = 0;

	printf("Enter the project name: ");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%s",project.projectName);

	printf("Enter the project description: ");
	fgets(project.description,sizeof(project.description),stdin);
    /*Enter member*/
	while(1)
	{
		printf("Enter the amount of member in your project: ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&member);
		if(member<=0)
		{
			printf("Member must be at least one person\n");
			continue;
		}
		else
		{
			name = (NAME_T*)calloc(member,sizeof(NAME_T));			/* allocate memory for NAME_T */
			if(name == NULL)
			{
				printf("Unable to allocate memory for %d members - exiting\n",member);
				exit(1);
			}
			printf("Enter both the first name and last name\n");
			for(i=0;i<member;i++)
			{
				printf("Enter the name of the member %d: ",i+1);
				fgets(input,sizeof(input),stdin);
				sscanf(input,"%s %s",name[i].firstName, name[i].lastName);
			}
			break;
		}
	}
	/*Enter task*/
	i = 0;
	while(1)
    {
		task = (TASK_T*)calloc(1,sizeof(TASK_T));					/* allocate memory for TASK_T */
		printf("Enter the task #%d[Press RETURN when done]: ",i+1);
		fgets(input,sizeof(input),stdin);
		strcpy(task->Topic,input);
        if(strcmp(task->Topic, "\n") == 0)
        {
            break;
        }
		printf("Enter the amount of day will use in this task: ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&task->Time);
		while(1)
        {
            printf("How many member will work on this task\n");
            fgets(input,sizeof(input),stdin);
            sscanf(input,"%d",&taskMember);
            if(taskMember <= 0)
            {
                printf("Need at least 1 member to responsible for the task\n");
            }
            else
            {
                break;
            }
        }
        task->responsMem = (NAME_T**)calloc(taskMember,sizeof(NAME_T*));		/* allocate memory for pointer of NAME_T */
        printf("Please assign the member(s) to this task\n");
        for(j=0;j<taskMember;j++)
        {
			task->responsMem[j] = (NAME_T*)calloc(1,sizeof(NAME_T)); 			/* allocate memory for NAME_T */
            printf("\tResponsible person[Press RETURN when done]: ");
            fgets(input,sizeof(input),stdin);
            sscanf(input,"%s %s",task->responsMem[j]->firstName,task->responsMem[j]->lastName);
			//printf("Name: %s %s\n",task->responsMem[j]->firstName,task->responsMem[j]->lastName);
		}
		printf("CHECK\n");
        task->memberCount = taskMember;
		i++;
		printf("CHECK\n");
		if(head == NULL)
        {
			printf("CHECK1\n");
            head = tail = task;     /*if there is no head on list yet set current task to be head and tail of list*/
        }
        else
        {
			printf("CHECK2\n");
            tail = task;                  /*if there is already a head on the list then set the current task to tail of the list*/
        }
		task = task->nextTask;                  /*Proceed to next structure in list*/
	}




	/*PRINT PROJECT NAME*/
	printf("\nProject Name: %s\n",project.projectName);
	printf("\t%s\n",project.description);
	printf("\nMember Name\n");	/* print all member name */
	for(i=0;i<member;i++)
	{
		printf("Member #%d : %s %s\n",i+1, name[i].firstName, name[i].lastName);
	}
	printf("\n");
	/*PRINT TASK*/
	task = head;
	printf("Task\n");
	while(task!=NULL)
    {
        printf("\nTask: %sTime: %d\n",task->Topic,task->Time);
        printf("Responsible person\n");
		for(j=0;j<taskMember;j++)
		{
			printf("Name: %s %s\n",task->responsMem[j]->firstName,task->responsMem[j]->lastName);
		}
		task = task->nextTask;
		if(task == NULL)
		{
			printf("NULLLLLLLLLLL\n");	/* DEBUG */
		}
    }
	free(name);
	free(task);

    return 0;
}
