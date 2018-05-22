/**********************************************
	loadFunctions.h
	<Header File>
	Handle the operation after the user chooses
	to load specific project.
	Either to update, delete or exit.

	By: Bhimapaka Thapanangkun
	ID: 60070503447
**********************************************/

/*loadFunctions.c*/
/*	Ask for the task number that the user wants to
	edit its status
	ARGUMENTS:	taskString - the choosen task that the user wanted to edit
*/
void chooseTask(char * taskString);



/*	Show the user what option they have after 
	successfully load a new file
*/
void displayOptions();

/**************************************************************/

/*projectEdit.c*/
void chooseEdit();
