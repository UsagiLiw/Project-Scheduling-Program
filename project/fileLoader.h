/*********************************************
	fileLoader.h
	<Header File>
	contains functions related to the read and
	load the project information within the file

	by Bhimapaka Thapanangkun
	ID: 60070503447
	DATE: 17/04/2018
**********************************************/

typedef struct _projectlist
{
	char projectName[128];			/*Store the name of the project*/
	struct _projectlist * pNext;	/*Point to the next project*/
}PROJECTLIST_T;

/*	Free the linked list from the data stored
	Arguments:	pHead - The head of the linked list that hold the first value
*/
void freeLinklist(PROJECTLIST_T * pHead);

/*	Break up member names from a string so that we can store it in the struct
	The names are being seperate by "," which act as a delimiter
	Argrument: tempNameString - The string with all the member names
								seperate by comma
*/
void breakNames(char * tempNameString);

/*	Read and break up data of each task.
	Information of each task is stored as a line with delimeters to 
	divide the type of data
	The information then being stored as graph
	Argument:	taskString - contains the data of a single task within the project
				taskCount - the count of the current task that the function is reading
*/
void readTask(char * taskString);

/*	Read the data within the project file and store and
	show the file
	Argument:	thisProject - the name of the project file that the user chooses
*/
void readProject(char * thisProject);

/*	Let the user chooses the project they want
	to load, the program then find the project name from the linked list
	Arguments:	pHead - The head of the linked list that hold the first value
*/
void chooseProject(PROJECTLIST_T * pHead,int count);

/*	Handle the read and store the project names 
	that exist within the database
	Argument:	pHead - The head of the linked list that hold the first value
*/
void projectNameList();


