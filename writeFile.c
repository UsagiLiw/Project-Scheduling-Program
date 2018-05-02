/*
* Name:Thanapat Sakaekhao 3430
* writeFile.c
* recieve all data and store in text file.

***** all pointer and string is temperary, everything still not match with other file******
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

void writeTaskData(PROJECTTASK_T, int taskCount)
{
	FILE* pOutTask = NULL;
	char tempProjectName[256];
	char temp[256];
	int i = 0;

	/* open or crete new text file to store data */
	strcpy(tempProjectName, project->name);
	sprintf(temp,"%s.txt",tempProjectName);
	pOutTask = fopen(temp, "w");
	fprintf(pOutTask, "%s;\n", project->name);
	fprintf(pOutTask, "%s;\n", project->info);
	fprintf(pOutTask, "%s;\n", project->member);
	pCurrentTask = pHead;
	while(pCurrentTask != NULL)
	{
		fprintf(pOutTask, "%s/%s/%d/%s;\n", pCurrentTask->name, 
											pCurrentTask->info, 
											pCurrentTask->timer, 
											pCurrentTask->person);
		pCurrentTask = pCurrentTask->pNext;
	}
	/*free data*/
	while(pCurrentTask != NULL)
	{
		pDelete = pCurrentTask;
		pCurrentTask = pCurrentTask->pNext;
		free(pDelete);
	}
	fclose(pOutTask);
	return 0;
}
/*
void writeAllProjectData()
{
	FILE* pOutAllProject
	int i = 0;
	
	pOutAllProject = fopen("allProject", "w");
	for(i = 0; i<projectCount, i++)
	{
		fprintf(pOutProject, "%s/%s;\n", project->name, project->info);
	}
	fclose(pOutAllProject);
	return 0;
}
*/
