/*********************************************
	fileLoader.h
	<Header File>
	contains functions related to the read and
	load the project information within the file

	by Bhimapaka Thapanangkun
	ID: 60070503447
	DATE: 17/04/2018
**********************************************/


/*	Read and break up data of each task.
	Information of each task is stored as a line with delimeters to 
	divide the type of data
	The information then being stored as graph
	Argument:	taskString - contains the data of a single task within the project
				taskCount - the count of the current task that the function is reading
*/
void readTask(char * taskString);

/*	Let the user chooses the project they want
	to load, the program then find the project name from the linked list
	Returns: 0 if the user doesn't want to continue and 1 if the user want 
			do something else with the project.
*/
int chooseProject();

void projectNameList();


