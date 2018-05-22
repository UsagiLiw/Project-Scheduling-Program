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

#include "abstractNetwork.h"
#include "fileLoader.h"
#include "projectInfo.h"
#include "dirent.h"

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
		retval = addEdge(pCurrent->Topic,token,pCurrent->Duration);
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
	char tempEdges[100];
	char name[128];
	char tempNameString[1000];
	TASK_T * pTempTask = NULL;
	char * token;

	pTempTask = (TASK_T*)calloc(1,sizeof(TASK_T));
	if(pTempTask == NULL)
	{
		printf("Error - Unable to allocate memory for a new task\n");
		exit(2);
	}
	sscanf(taskString,"%[^|]|%[^|]|%d|%[^|]|%[^|]|%d;",pTempTask->Topic
														,pTempTask->taskDescription
														,&pTempTask->Duration
														,pTempTask->taskMember
														,tempEdges
														,&pTempTask->Status);
	printf("\n|%s|\n",pTempTask->Topic);
	printf("\t%s\n",pTempTask->taskDescription);
	printf("Duration: %d days\n",pTempTask->Duration);
	printf("Responsible member: %s\n",pTempTask->taskMember);
	strcpy(pTempTask->dependencyString,tempEdges);
	if(pTempTask->Status == 1)
		printf("Status: DONE\n");
	else
		printf("Status: IN PROGRESS\n");
	addVertex(pTempTask->Topic,pTempTask);
	dependencyHandler(pTempTask,tempEdges);
	printf("\n");
}

/*	Read the data within the project file and store and
	show the file
	Argument:	thisProject - the name of the project file that the user chooses
	RETURN:		status - to say whether to progress to the next operation or not
*/
int chooseProject()
{
	FILE * project = NULL;
	char chooseProject[256];
	char projectDirectory[] = "savefile/";
	char stringInput[1000];
	char tempNameString[1000];
	int numberOfTask = 0;
	int status = 0;
	TASK_T * pCurrent = NULL;
	TASK_T * pTask = NULL;
		
	while(1)
	{
		strcpy(projectDirectory,"savefile/");
		printf("Choose the project name [Press RETURN to go back] : ");
		memset(stringInput,0,sizeof(stringInput));
		fgets(stringInput,sizeof(stringInput),stdin);
		/*In case user wanted to return to menu instead of choosing file*/
		if(strcmp(stringInput,"\n") == 0)
		{
			printf("\tReturn to main menu\n\n");
			status = 0;
			break;
		}
		sscanf(stringInput,"%[^\n]",chooseProject);
		strcat(projectDirectory,chooseProject);
		project = fopen(projectDirectory,"r");
		if(project == NULL)
		{
			printf("Error - Unable to find the designated project.\n");
			printf("Wrong name or might missing <.txt>)\n\n");
		}
		else
		{	
			strcpy(thisProject,chooseProject);
			NUMBEROFTASK = 0;
			fgets(stringInput,sizeof(stringInput),project);			/*Get the project name*/
			sscanf(stringInput,"%[^;]",CHOSENPROJECT.projectName);
			printf("Project:\n\t%s\n\n",CHOSENPROJECT.projectName);
			fgets(stringInput,sizeof(stringInput),project);
			sscanf(stringInput,"%[^;]",CHOSENPROJECT.initDate);
			printf("Started on: %s\n\n",CHOSENPROJECT.initDate);
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
			}
			else
			{
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
			}	
			fclose(project);	
			status = 1;			
			break;			
		}
	}
	return status;
}

void projectNameList()
{
	DIR * dp = NULL;
	struct dirent * dptr = NULL;
	
	if(NULL == (dp = opendir("savefile/")))
	{
		printf("Error - Unable to find the save folder of the project\n\n");
		exit(1);
	}
	while(NULL != (dptr = readdir(dp)))
	{
		printf(" [ %s ]\n",dptr->d_name);
	}
	closedir(dp);
}


