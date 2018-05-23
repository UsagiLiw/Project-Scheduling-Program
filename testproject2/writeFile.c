/***************************************************************
	writeFile.c
	Handle the write data onto file operations
	for the whole project.

	By Bhimapaka Thapanangkun
	ID: 60070503447
***************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include "projectInfo.h"
#include "abstractNetwork.h"

MEMBER_T * pHead = NULL;
MEMBER_T * pTail = NULL;

void deleteFile()
{
	int ret = 0;
	char answer[32];
	char projectDirectory[] = "savefile/";
	char projectType[] = ".txt";

	printf("Are you sure you want to delete %s project?\n",CHOSENPROJECT.projectName);
	printf("[Y/N] :");
	fgets(answer,sizeof(answer),stdin);
	if ((answer[0] == 'Y') || (answer[0] == 'y'))
	{
		strcat(projectDirectory,CHOSENPROJECT.projectName);
		strcat(projectDirectory,projectType);
		ret = remove(projectDirectory);
		if(ret == 0)
			printf("%s successfully deleted\n",thisProject);
		else
		{
			printf("Error - Unable to delete %s, program terminated\n",thisProject);
			exit(3);
		}
	}
}

void printProjectInfo()
{
	MEMBER_T * pMember = pHead;
	VERTEX_T * pVertex = vListHead;
	VERTEX_T * pVertex2 = NULL;
	int i,count = 0,depCount;
	char ** adjacentKeys;

	printf("Project:\n\t%s\n\n",CHOSENPROJECT.projectName);
	printf("Description:\n\t%s\n\n",CHOSENPROJECT.description);
	printf("Member(s):\n");
	while(pMember != NULL)
	{
		printf("\t- %s\n",pMember->memberName);
		pMember = pMember->pNext; 	
	}
	
	while(pVertex != NULL)
	{
		printf("\n | %s |\n",pVertex->data->Topic);
		printf("Description: %s\n",pVertex->data->taskDescription);
		printf("Duration: %d days\n",pVertex->data->Duration);
		printf("Responsible members: %s\n",pVertex->data->taskMember);
		if(pVertex->data->Status == 1)
			printf("Status: DONE\n");
		else
			printf("Status: IN PROGRESS\n");
		printf("Requirement: ");
		/*depCount = 0;
		while(pVertex2 != NULL)
		{
			printf("\n");
			if(findEdge(pVertex2->key,pVertex->key) > 0)
			{
				printf("\t - %s",pVertex2->key);
				depCount++;
			}
			pVertex2 = pVertex2->next;
		}
		if(depCount == 0)
		{
			printf("No Prior Requirement\n");
		}*/
		adjacentKeys = getDependencyVertices(pVertex->key,&count);
		if(count > 0)
		{
			for(i = 0; i < count; i++)
			{
				printf("\n\t - %s",adjacentKeys[i]);
				free(adjacentKeys[i]);
			}
			count = 0;
			free(adjacentKeys);
		}
		else
			printf("No prior requirement\n");
		pVertex = pVertex->next;
	}
	printf("\n\n");
}


/*	Break up member names from a string so that we can store it in the struct
	The names are being seperate by "," which act as a delimiter
	Argrument: tempNameString - The string with all the member names
								seperate by comma
*/
void breakNames(char * tempNameString)
{	
	char * token;	
	MEMBER_T * pMember = NULL;
	memCount = 0;
	token = strtok(tempNameString,",");
	//printf("Member(s):\n");
	do
	{
		pMember = (MEMBER_T*) calloc(1,sizeof(MEMBER_T));
		if(pMember == NULL)
		{
			printf("Error - Unable to allocate memory for a new member\n");
			exit(2);
		}
		else
		{ 
			strcpy(pMember->memberName,token);
			if(pHead == NULL)
			{
				pHead = pMember;
			}
			else
			{
				pTail->pNext = pMember;
			}
			pTail = pMember;
			//printf("\t- %s\n",token);
			memCount++;
			token = strtok(NULL,",");
		}
	}while(token != NULL);
	//printf("\nFound %d members\n\n",memCount);
}

void saveEdit()
{
	FILE * pOut = NULL;
	MEMBER_T * pMember = NULL;
	VERTEX_T * pVertex = vListHead;
	VERTEX_T * pVertex2 = NULL;
	char nameString[1000];
	char projectDirectory[] = "savefile/";
	char fileType[] = ".txt";
	int i,count = 0;
	char ** adjacentKeys;
	
	strcat(projectDirectory,CHOSENPROJECT.projectName);
	strcat(projectDirectory,fileType);
	pOut = fopen(projectDirectory,"w");
	if(fopen == NULL)
	{
		printf("Error - Unable to open and write on %s\n",projectDirectory);
		exit(3);	
	}
	fprintf(pOut,"%s;\n",CHOSENPROJECT.projectName);
	fprintf(pOut,"%s;\n",CHOSENPROJECT.initDate);
	fprintf(pOut,"%s;\n",CHOSENPROJECT.description);
	pMember = pHead;
	//memset(nameString,0,sizeof(nameString));
	for(i = 0; i < memCount; i++)
	{
		fprintf(pOut,"%s",pMember->memberName);
		if(i < memCount - 1)
		{
			fprintf(pOut,",");
		}
		pMember = pMember->pNext; 	
	}
	fprintf(pOut,";\n");
	while(pVertex != NULL)
	{
		fprintf(pOut,"%s|%s|%d|",pVertex->data->Topic
							,pVertex->data->taskDescription
							,pVertex->data->Duration);
		fprintf(pOut,"%s|",pVertex->data->taskMember);
		adjacentKeys = getDependencyVertices(pVertex->key,&count);
		if(count > 0)
		{
			for(i = 0; i < count; i++)
			{
				fprintf(pOut,"%s",adjacentKeys[i]);
				if(i < count - 1)
				{
					fprintf(pOut,",");
				}
				free(adjacentKeys[i]);
			}
			free(adjacentKeys);
		}
		else
		{
			fprintf(pOut,"NONE");
		}
		fprintf(pOut,"|%d;\n",pVertex->data->Status);	
		pVertex = pVertex->next;
	}
	fclose(pOut);
}
