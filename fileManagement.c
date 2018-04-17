/*********************************************
	fileManagement.c
	contains functions related to the read and
	write of the projects within the file

	by Bhimapaka Thapanangkun
	ID: 60070503447
	DATE: 17/04/2018
**********************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "fileManagement.h"

typedef struct _projectlist
{
	char projectName[128];			/*Store the name of the project*/
	struct _projectlist * pNext;	/*Point to the next project*/
}PROJECTLIST_T;

/*
	Handle the read and store the project names 
	that exist within the database
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
		memset(tempName,0,sizeof(tempName));
		sscanf(stringInput,"%s",tempName);
		pProject = (PROJECTLIST_T*) calloc(1,sizeof(PROJECTLIST_T));
		if(pProject == NULL)
		{
			printf("ERROR - Unable to allocate memory for project list\n");
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
	printf("Found %d projects stored\n\n",count+1);
	fclose(nameFile);
}
