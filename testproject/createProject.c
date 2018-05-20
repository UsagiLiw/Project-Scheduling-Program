/****************************************
	createProject.c

	This file contains function for creating
	a new project

	By: Bhimapaka Thapanangkun
	ID: 60070503447
****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "abstractGraph.h"
#include "loadFunctions.h"
#include "projectInfo.h"
#include "ioFunctions.h"

void addDependency()
{
	char stringInput[128];	
	char fromTask[128];	
	char toTask[128];
	int status = 1;

	while(1)
	{
		memset(stringInput,0,sizeof(stringInput));
		printf("Please specify the dependencies between tasks\n");
		printDepthFirst();
		memset(fromTask,0,sizeof(fromTask));
		memset(toTask,0,sizeof(toTask));
		printf("Enter FROM task [Press RETURN when done] : ");
		fgets(stringInput,sizeof(stringInput),stdin);
		if(strcmp(stringInput,"\n") == 0)
			break;
		sscanf(stringInput,"%s",fromTask);
		printf("Enter TO task :");
		memset(stringInput,0,sizeof(stringInput));
		fgets(stringInput,sizeof(stringInput),stdin);
		sscanf(stringInput,"%s",toTask);
		status = addEdge(fromTask,toTask);
		if(status == 1)
		{
			printf("Link From | %s | to | %s |\n",fromTask,toTask);
		}
		else if(status == -1)
		{
			printf("Error - An edge between | %s | and | %s | already exist\n",fromTask,toTask);
		}		
		else
		{
			printf("Error - One or both vertex are not found\n");
		}
	}
}

void addTaskMember(TASK_T ** pCurrent)
{
	char tempName[128];
	char stringInput[128];
	char tempNameString[1000];
	char comma[] = ",";
	int memCount = 0;
	TASKMEMBER_T * pTaskMem = NULL;
	TASKMEMBER_T * pTail = NULL;

	memset(tempNameString,0,sizeof(tempNameString));
	while(1)
	{
		printf("Enter responsible member name NO.%d [Press RETURN when done]: ",memCount+1);
		memset(stringInput,0,sizeof(stringInput));	
		fgets(stringInput,sizeof(stringInput),stdin);
		if(strcmp(stringInput,"\n") == 0)
		{
			if(memCount <= 0)
			{
				printf("Must have at least one responsible member\n");
				continue;
			}
			else
				break;
		}
		sscanf(stringInput,"%s",tempName);
		pTaskMem = (TASKMEMBER_T*) calloc(1,sizeof(TASKMEMBER_T));
		if(pTaskMem == NULL)
		{
			printf("Error - Unable to allocate memory for Task Member\n");
			exit(2);
		}
		strcpy(pTaskMem->tName,tempName);
		strcat(tempNameString,tempName);
		strcat(tempNameString,comma);
		if((*pCurrent)->nameHead == NULL)
		{
			(*pCurrent)->nameHead = pTaskMem;
		}
		else
		{
			pTail->pNext = pTaskMem;
		}
		pTail = pTaskMem;
		memCount++;
	}
	tempNameString[strlen(tempNameString) - 1] = '\0';
	strcpy((*pCurrent)->memberNameString,tempNameString);
}

void enterProjectMember()
{
	pHead = NULL;
	pTail = NULL;
	
	char tempName[128];
	char stringInput[128];
	int memCount = 0;
	MEMBER_T * pMember = NULL;
	
	while(1)
	{
		printf("Enter member name NO.%d [Press RETURN when done]: ",memCount+1);
		memset(stringInput,0,sizeof(stringInput));
		memset(tempName,0,sizeof(tempName));	
		fgets(stringInput,sizeof(stringInput),stdin);
		if(strcmp(stringInput,"\n") == 0)
		{
			if(memCount <= 0)
			{
				printf("Must have at least one member\n");
				continue;
			}
			else
				break;
		}
		if(symbolCheck(stringInput) == 0)
		{
			printf("Error - < ; , | > symbols are not allow in the input\n");
			continue;
		}
		sscanf(stringInput,"%s",tempName);
		pMember = (MEMBER_T*) calloc(1,sizeof(MEMBER_T));
		if(pMember == NULL)
		{
			printf("Error - Unable to allocate memory\n");
			exit(2);
		}
		strcpy(pMember->memberName,tempName);
		if(pHead == NULL)
		{
			pHead = pMember;
		}
		else
		{
			pTail->pNext = pMember;
		}
		pTail = pMember;
		memCount++;
	}
}

void newProject()
{
	char stringInput[1000];
	char projectNameString[1000];
	int memCount = 0;
	char comma[] = ",";
	TASK_T * pCurrent = NULL;

	NUMBEROFTASK = 0;
	while(1)
	{
		printf("Enter the project name: ");
		memset(stringInput,0,sizeof(stringInput));	
		fgets(stringInput,sizeof(stringInput),stdin);
		if(symbolCheck(stringInput) == 0)
		{
			printf("Error - < ; , | > symbols are not allow in the input\n");
			continue;
		}
		sscanf(stringInput,"%s",CHOSENPROJECT.projectName);
		printf("\n\n");
		break;
	}
	while(1)
	{
		printf("Description of the project: \n");
		memset(stringInput,0,sizeof(stringInput));	
		fgets(stringInput,sizeof(stringInput),stdin);
		if(symbolCheck(stringInput) == 0)
		{
			printf("Error - < ; , | > symbols are not allow in the input\n");
			continue;
		}
		sscanf(stringInput,"%s",CHOSENPROJECT.description);
		printf("\n\n");
		enterProjectMember();
		printf("\n\n");
		initGraph(100,1);
		break;
	}
	while(1)
	{
		pCurrent = (TASK_T*) calloc(1,sizeof(TASK_T));
		if(pCurrent == NULL)
		{
			printf("Error - Unable to allocate memory for a new task\n");
			exit(2);
		}
		printf("Enter task name NO.%d [Press RETURN when done]: ",NUMBEROFTASK+1);
		memset(stringInput,0,sizeof(stringInput));	
		fgets(stringInput,sizeof(stringInput),stdin);
		if(strcmp(stringInput,"\n") == 0)
		{
			if(NUMBEROFTASK <= 0)
			{
				printf("Must have at least one task\n");
				continue;
			}
			else
				break;
		}
		if(symbolCheck(stringInput) == 0)
		{
			printf("Error - < ; , | > symbols are not allow in the input\n");
			continue;
		}
		sscanf(stringInput,"%s",pCurrent->Topic);
		printf("Enter task description: ");
		memset(stringInput,0,sizeof(stringInput));	
		fgets(stringInput,sizeof(stringInput),stdin);
		if(symbolCheck(stringInput) == 0)
		{
			printf("Error - < ; , | > symbols are not allow in the input\n");
			continue;
		}
		sscanf(stringInput,"%s",pCurrent->taskDescription);
		printf("Duration(days) of this task: ");
		memset(stringInput,0,sizeof(stringInput));	
		fgets(stringInput,sizeof(stringInput),stdin);
		if(symbolCheck(stringInput) == 0)
		{
			printf("Error - < ; , | > symbols are not allow in the input\n");
			continue;
		}
		sscanf(stringInput,"%d",&pCurrent->Duration);
		addTaskMember(&pCurrent);
		//printf("%s;\n",pCurrent->memberNameString);
		strcpy(pCurrent->dependencyString,"NONE");
		pCurrent->Status = -1;
		if(addVertex(pCurrent->Topic,pCurrent) == 0)
		{
			printf("Error - task: %s already exist\n",pCurrent->Topic); 
		}
		printf("\n");
		NUMBEROFTASK++;
	}
}
