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
	int count = 0,length = 0;	
	char * token;	
	MEMBER_T * pCurrent = NULL;
	MEMBER_T * pMember = NULL;

	token = strtok(tempNameString,",");
	printf("Member(s):\n");
	while(token != NULL)
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
		printf("\t%s\n",pMember->memberName);
		count++;
		token = strtok(NULL,",");
	}
	printf("\nFound %d members\n\n",count);
}

/*	Read and break up data of each task.
	Information of each task is stored as a line with delimeters to 
	divide the type of data
*/
void readTask(char * taskString)
{
	
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
		fgets(stringInput,sizeof(stringInput),project);			/*Get the project name*/
		sscanf(stringInput,"%[^;]",CHOSENPROJECT.projectName);
		printf("Project:\n\t%s\n\n",CHOSENPROJECT.projectName);
		fgets(stringInput,sizeof(stringInput),project);			/*Get the project description*/
		sscanf(stringInput,"%[^;]",CHOSENPROJECT.description);
		printf("Description:\n\t%s\n\n",CHOSENPROJECT.description);
		fgets(stringInput,sizeof(stringInput),project);			/*Get the members*/
		sscanf(stringInput,"%[^;]",tempNameString);
		breakNames(tempNameString);		

		/*There can be finite number of task so we loop to store each task in linked list*/
		while(fgets(stringInput,sizeof(stringInput),project) != NULL)
		{
			readTask(stringInput);	
		}							
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
			//free(pProject);
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


