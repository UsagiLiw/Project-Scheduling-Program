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

#include "abstractNetwork.h"
#include "loadFunctions.h"
#include "projectInfo.h"
#include "ioFunctions.h"

void addDependency()
{
	char stringInput[128];	
	char fromTask[128];	
	char toTask[128];
	int status = 1;
	TASK_T * pFrom = NULL;

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
		sscanf(stringInput,"%[^\n]",fromTask);
		pFrom = findVertex(fromTask);
		if(pFrom == NULL)
		{
			continue;
		}
		printf("Enter TO task :");
		memset(stringInput,0,sizeof(stringInput));
		fgets(stringInput,sizeof(stringInput),stdin);
		sscanf(stringInput,"%[^\n]",toTask);
		status = addEdge(fromTask,toTask,pFrom->Duration);
		if(status == 1)
		{
			printf("Linked From | %s | to | %s |\n",fromTask,toTask);
		}
		else if(status == -1)
		{
			printf("Error - An edge between | %s | and | %s | already exist\n\n",fromTask,toTask);
		}		
		else
		{
			printf("Error - One or both vertex are not found\n\n");
		}		
		pFrom = NULL;
	}
}

void addTaskMember(TASK_T ** pCurrent)
{
	char tempName[128];
	char stringInput[128];
	int bOk = 0;
	MEMBER_T * pMember = NULL;

	while(1)
	{
		bOk = 0;
		printf("Enter responsible member name for this task : ");
		memset(stringInput,0,sizeof(stringInput));	
		fgets(stringInput,sizeof(stringInput),stdin);
		sscanf(stringInput,"%[^\n]",tempName);
		pMember = pHead;
		while(pMember != NULL)
		{
			if(strcmp(pMember->memberName,tempName) == 0)	
			{
				bOk = 1;
				break;
			}
			pMember = pMember->pNext;
		}
		if(bOk == 1)
		{
			strcpy((*pCurrent)->taskMember,tempName);
			break;
		}
		else
		{
			printf("Error - The name is not one of the existing member\n\n");
		}
	}
}

void enterProjectMember()
{
	pHead = NULL;
	pTail = NULL;
	
	char tempName[128];
	char stringInput[128];
	int bOk = 1;
	MEMBER_T * pMember = NULL;
	MEMBER_T * pMemCheck = NULL;
	
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
				printf("Must have at least one member\n\n");
				continue;
			}
			else
				break;
		}
		if(symbolCheck(stringInput) == 0)
		{
			printf("Error - < ; | , > symbols are not allow in the input\n\n");
			continue;
		}
		sscanf(stringInput,"%[^\n]",tempName);
		pMemCheck = pHead;
		bOk = 1;
		while(pMemCheck != NULL)
		{
			if(strcmp(pMemCheck->memberName,tempName) == 0)	
			{
				bOk = 0;
				printf("Error - This name already exist, please use something else\n\n");
				break;
			}
			pMemCheck = pMemCheck->pNext;
		}
		if(bOk == 1)
		{
			pMember = (MEMBER_T*) calloc(1,sizeof(MEMBER_T));
			if(pMember == NULL)
			{
				printf("Error - Unable to allocate memory\n\n");
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
		if(strcmp(stringInput,"\n") == 0)
		{
			printf("Error - Cannot leave project name empty\n\n");
			continue;
		}
		if(symbolCheck(stringInput) == 0)
		{
			printf("Error - < ; | , > symbols are not allow in the input\n\n");
			continue;
		}
		sscanf(stringInput,"%[^\n]",CHOSENPROJECT.projectName);
		strcpy(thisProject,CHOSENPROJECT.projectName);
		printf("\n\n");
		break;
	}
	while(1)
	{
		printf("Enter the project starting date [yyyy-mm-dd]: ");
		memset(stringInput,0,sizeof(stringInput));	
		fgets(stringInput,sizeof(stringInput),stdin);
		stringInput[strlen(stringInput) - 1] = '\0';
		if(strcmp(stringInput,"\n") == 0)
		{
			printf("Error - Cannot leave the date empty\n\n");
			continue;
		}
		if(checkDate(stringInput) == 0)
		{
			continue;
		}
		sscanf(stringInput,"%[^\n]",CHOSENPROJECT.initDate);
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
			printf("Error - < ; | , > symbols are not allow in the input\n\n");
			continue;
		}
		if(strcmp(stringInput,"\n") == 0)
		{
			strcpy(CHOSENPROJECT.description,"NONE");
		}
		else
		{
			sscanf(stringInput,"%[^\n]",CHOSENPROJECT.description);
		}
		printf("\n\n");
		break;
	}
	enterProjectMember();
	printf("\n\n");
	initGraph(100,1);
	while(1)
	{
		pCurrent = (TASK_T*) calloc(1,sizeof(TASK_T));
		if(pCurrent == NULL)
		{
			printf("Error - Unable to allocate memory for a new task\n\n");
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
			printf("Error - < ; | , > symbols are not allow in the input\n\n");
			continue;
		}
		sscanf(stringInput,"%[^\n]",pCurrent->Topic);
		while(1)
		{
			printf("Enter task description: ");
			memset(stringInput,0,sizeof(stringInput));	
			fgets(stringInput,sizeof(stringInput),stdin);
			if(symbolCheck(stringInput) == 0)
			{
				printf("Error - < ; | , > symbols are not allow in the input\n\n");
				continue;
			}
			if(strcmp(stringInput,"\n") == 0)
			{
				strcmp(pCurrent->taskDescription,"NONE");
			}
			else
			{
				sscanf(stringInput,"%[^\n]",pCurrent->taskDescription);
			}			
			break;
		}
		while(1)
		{
			printf("Duration(days) of this task: ");
			memset(stringInput,0,sizeof(stringInput));	
			fgets(stringInput,sizeof(stringInput),stdin);
			stringInput[strlen(stringInput) - 1] = '\0';
			if(isDigitString(stringInput) == 0)
			{
				printf("Error - Only numerics are allow\n\n");
				continue;
			}
			sscanf(stringInput,"%d",&pCurrent->Duration);
			break;
		}
		addTaskMember(&pCurrent);
		//printf("%s;\n",pCurrent->memberNameString);
		//strcpy(pCurrent->dependencyString,"NONE");
		pCurrent->Status = -1;
		if(addVertex(pCurrent->Topic,pCurrent) != 1)
		{
			printf("\nError - task: %s already exist\n\n",pCurrent->Topic); 
		}
		printf("\n");
		NUMBEROFTASK++;
	}
	
}
