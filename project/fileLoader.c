/*********************************************
	fileLoader.c
	contains functions related to the load and
	read the project information within the file

	by Bhimapaka Thapanangkun
	ID: 60070503447
	DATE: 17/04/2018
**********************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "abstractGraph.h"
#include "fileLoader.h"
#include "projectInfo.h"


/*	Free the linked list from the data stored
	Arguments:	pHead - The head of the linked list that hold the first value
*/
void freeLinklist(PROJECTLIST_T * pHead)
{
	PROJECTLIST_T * pDelete = NULL;
	PROJECTLIST_T * pCurrent = NULL;
	
	pCurrent = pHead;
	while(pCurrent != NULL)
	{
		pDelete = pCurrent;
		pCurrent = pCurrent->pNext;
		free(pDelete);
	}
}

/*	Break up member names from a string so that we can store it in the struct
	The names are being seperate by "," which act as a delimiter
	Argrument: tempNameString - The string with all the member names
								seperate by comma
*/
void breakNames(char * tempNameString)
{
	int count = 0;	
	char * token;	
	MEMBER_T * pCurrent = NULL;
	MEMBER_T * pMember = NULL;

	token = strtok(tempNameString,",");
	printf("Member(s):\n");
	do
	{
		pMember = (MEMBER_T*)calloc(1,sizeof(MEMBER_T));
		if(pMember == NULL)
		{
			printf("Error - Unable to allocate memory for a new member\n");
			exit(2);
		} 
		strcpy(pMember->memberName,token);
		if(MEMBER == NULL)
		{
			MEMBER = pMember;
		}
		if(pCurrent == NULL)
		{
			pCurrent = MEMBER;
		}
		pCurrent = pCurrent->pNext;
		printf("\t- %s\n",pMember->memberName);
		count++;
		token = strtok(NULL,",");
	}while(token != NULL);
	printf("\nFound %d members\n\n",count);
}

/*	Break up dependency information of the task 
	seperated by "," delimiter then let addEdges function 
	operates on adding edges
	Argument: pCurrent - The data of the current task that we are looking at
			  tempEdges - String holding all the dependency of the task 
						  ("-1" if no dependency) 
*/
void dependencyHandler(TASK_T * pCurrent,char * tempEdges)
{
	char * token;
	char dependency[100];
	int retval = 0;				/*In case of bug*/

	token = strtok(tempEdges,",");
	printf("Requirement:\n");
	do
	{
		sscanf(token,"%s",dependency);
		if(strcmp(token,"NONE") == 0)
		{
			printf("\tNo prior requirement\n");
			break;
		}
		retval = addEdge(pCurrent->Topic,token);
		printf("\t- %s\n",token);
		token = strtok(NULL,",");
	}while(token != NULL);
}

/*	Read and break up data of each task.
	Information of each task is stored as a line with delimeters to 
	divide the type of data
	The information then being stored as graph
	Argument:	taskString - contains the data of a single task within the project
				taskCount - the count of the current task that the function is reading
*/
void readTask(char * taskString)
{
	char tempNameString[1000];
	char tempEdges[100];
	char * token;
	int retval = 0;
	TASK_T * pCurrent = NULL;
	TASKMEMBER_T * pMember = NULL;
	TASKMEMBER_T * pCurrentMember = NULL;

	pCurrent = (TASK_T*)calloc(1,sizeof(TASK_T));
	if(pCurrent == NULL)
	{
		printf("Error - Unable to allocate memory for a new task\n");
		exit(2);
	}
	sscanf(taskString,"%d|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d;",&pCurrent->taskNumber
														,pCurrent->Topic
														,pCurrent->taskDescription
														,&pCurrent->Duration
														,tempNameString
														,tempEdges
														,&pCurrent->Status);
	printf("|%d| %s\n",pCurrent->taskNumber,pCurrent->Topic);
	printf("\t%s\n",pCurrent->taskDescription);
	printf("Duration: %d days\n",pCurrent->Duration);
	printf("Responsible members:\n");
	token = strtok(tempNameString,",");
	do
	{
		pMember = (TASKMEMBER_T*)calloc(1,sizeof(TASKMEMBER_T));
		if(pMember == NULL)
		{
			printf("Error - Unable to allocate memory for a new member\n");
			exit(2);
		} 
		strcpy(pMember->name,token);
		if(pCurrent->taskMember == NULL)
		{
			pCurrent->taskMember = pMember;
		}
		if(pCurrentMember == NULL)
		{
			pCurrentMember = pCurrent->taskMember;
		}
		pCurrentMember = pCurrentMember->pNext;
		printf("\t- %s\n",pCurrent->taskMember->name);
		pCurrent->taskMember = pCurrent->taskMember->pNext;
		token = strtok(NULL,",");	
	}while(token != NULL);
	if(pCurrent->Status == 1)
		printf("Status: DONE\n");
	else
		printf("Status: IN PROGRESS\n");
	retval = addVertex(pCurrent->Topic,pCurrent);
	dependencyHandler(pCurrent,tempEdges);
	printf("\n");
}

/*	Read the data within the project file and store and
	show the file
	Argument:	thisProject - the name of the project file that the user chooses
*/
void readProject(char * thisProject)
{
	FILE * project = NULL;
	char textType[] = ".txt";
	char projectName[] = "savefile/";
	char stringInput[1000];
	char tempNameString[1000];
	int numberOfTask = 0;
	TASK_T * pCurrent = NULL;
	TASK_T * pTask = NULL;
	
	strcat(thisProject,textType);
	strcat(projectName,thisProject);
	project = fopen(projectName,"r");
	if(project == NULL)
	{
		printf("Error - Unable to find the designated project\n");
	}
	else
	{
		NUMBEROFTASK = 0;
		fgets(stringInput,sizeof(stringInput),project);			/*Get the project name*/
		sscanf(stringInput,"%[^;]",CHOSENPROJECT.projectName);
		printf("Project:\n\t%s\n\n",CHOSENPROJECT.projectName);
		fgets(stringInput,sizeof(stringInput),project);			/*Get the project description*/
		sscanf(stringInput,"%[^;]",CHOSENPROJECT.description);
		printf("Description:\n\t%s\n\n",CHOSENPROJECT.description);
		fgets(stringInput,sizeof(stringInput),project);			/*Get the members*/
		sscanf(stringInput,"%[^;]",tempNameString);
		breakNames(tempNameString);		
		fgets(stringInput,sizeof(stringInput),project);
		sscanf(stringInput,"%d",&numberOfTask);
		if(numberOfTask == 0)
		{
			printf("\nThis project has no task yet!\n");
			exit(0);
		}
		printf("This project has %d tasks:\n",numberOfTask);
		NUMBEROFTASK = numberOfTask;
		/*There can be finite number of task so we loop to store each task in graph*/
		initGraph(numberOfTask,1);
		while(fgets(stringInput,sizeof(stringInput),project) != NULL)
		{
			if(strcmp(stringInput,"\n") == 0)
				continue;
			readTask(stringInput);	
		}
		fclose(project);							
	}
}

/*	Let the user chooses the project they want
	to load, the program then find the project name from the linked list
	Arguments:	pHead - The head of the linked list that hold the first value
*/
void chooseProject(PROJECTLIST_T * pHead,int count)
{
	char stringInput[64];
	int choose = 0;
	int i;
	PROJECTLIST_T * pCurrent = NULL;
	
	while(1)
	{
		printf("Choose the project number [Press RETURN to go back] :");
		fgets(stringInput,sizeof(stringInput),stdin);
		/*In case user wanted to return to menu instead of choosing file*/
		if(strcmp(stringInput,"\n") == 0)
		{
			printf("\tReturn to main menu\n\n");
			out = 0;
			break;
		}
		sscanf(stringInput,"%d",&choose);
		if((choose > count) || (choose < 0))
		{
			printf("\tMust be numerical number of the project that exist in the list\n\n");
			continue;
		}
		else
		{
			out = 1;
			break;
		}
	}	
	if(out == 1)
	{
		/*Looking through the stored linked list for the project that the user choosed*/
		pCurrent = pHead;
		for(i = 1;i < choose; i++)
		{
			pCurrent = pCurrent->pNext; 		
		} 
		printf("\tYou choose : %s\n\n",pCurrent->projectName);
		strcpy(thisProject,pCurrent->projectName);		/*thisProject is a global variable in fileLoader.h*/
	}
	freeLinklist(pHead);
}

/*	Handle the read and store the project names 
	that exist within the database into a linked list
*/
void projectNameList()
{
	char stringInput[128];
	char tempName[128];
	int count = 0;
	
	PROJECTLIST_T * pHead = NULL;
	PROJECTLIST_T * pTail = NULL;
	PROJECTLIST_T * pCurrent = NULL;
	PROJECTLIST_T * pProject = NULL;
	FILE * nameFile = NULL;
	
	nameFile = fopen("savefile/projectList.txt","r");
	if(nameFile == NULL)
	{
		printf("ERROR - Unable to read project file, PROGRAM TERMINATED\n");
		exit(0);
	}
	while(fgets(stringInput,sizeof(stringInput),nameFile) != NULL)
	{
		/*Skip empty line in case of bug*/
		if(strcmp(stringInput,"\n") == 0)
			continue;
		memset(tempName,0,sizeof(tempName));
		sscanf(stringInput,"%[^\n]",tempName);
		/*Store the project list as a linked list*/
		pProject = (PROJECTLIST_T*) calloc(1,sizeof(PROJECTLIST_T));
		if(pProject == NULL)
		{
			printf("ERROR - Unable to allocate memory for project list\n\n");
			exit(1);
		}
		printf("\t%d.%s\n",count+1,tempName);
		strncpy(pProject->projectName,tempName,sizeof(pProject->projectName)-1);
		if(pHead == NULL)
		{
			pHead = pTail = pProject;
		}
		else
		{
			pTail->pNext = pProject;
			pTail = pProject;
			pTail->pNext = NULL;
		}
		if(pCurrent == NULL)
		{
			pCurrent = pHead;
		}
		pCurrent = pCurrent->pNext;
		count++;
	}
	printf("Found %d projects stored\n\n",count);
	fclose(nameFile);
	chooseProject(pHead,count);
}


