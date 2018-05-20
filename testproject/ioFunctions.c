/*  
 * ioFunctions.c
 *
 * Defines a number of useful functions for getting different data
 * types and also for checking for strings of digits or non-digits.
 *
 * Created by Sally Goldin, 31 August 2010 for CPE 100 demonstration
 * Updated 18 Oct 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ioFunctions.h"


/*	Check for the symbol that should not be allow 
	for the input. As these symbols act as a delimiter
	for the program to read the file
	Returns 1 if all are not either "," "|" ";", 0 if 
	found any of them in the input
*/
int symbolCheck(char * string)
{
	char * symbol = ",|;";
	int bOk = 1;
	int i;
	for (i = 0; i < strlen(string); i++)
	{
		if (strchr(symbol,string[i]) != NULL) 
		{
			bOk = 0;
			break; 
		}
	}
	return bOk;
}

/*  Check that a string contains only digits.
 *  testString  - String to be checked
 *  Returns 1 if all digits, 0 if not
 */
int isDigitString(char* testString)
{
	int bOk = 1;  /* status flag to be returned */
	int i;
	for (i = 0; i < strlen(testString); i++)
	{
		if (!isdigit(testString[i]))
		{
			bOk = 0;
			break;
		}
	}
	return bOk;
}

/*  Check that a string contains only alphabetic characters.
 *  (No punctuation, digits or white space allowed)
 *  testString  - String to be checked
 *  Returns 1 if all alpha chars, 0 if not
 */
int isAlphaString(char* testString)
{
	int bOk = 1;  /* status flag to be returned */
	int i;
	for (i = 0; i < strlen(testString); i++)
	{
		if (!isalpha(testString[i]))
		{
			bOk = 0;
			break;
		}
	}
	return bOk;
}

/* Get an integer value from the user that is between
 * a specified min and max value. Keeps asking until 
 * the user enters a valid value.
 * prompt - Message to print to ask the user for the value
 * min    - Smallest acceptable value for the integer
 * max    - Largest acceptable value for the integer
 * Returns the final, correct integer entered by the user.
 */
int getLimitedInteger(char* prompt, int min, int max)
{ 
    char input[CHARMAX]; /* buffer for getting data */ 
    int tempvalue;  /* holds value while we are checking */
    int bOkValue = 0;  /* Controls loop. We will loop until */
                       /* bOkValue becomes true. */  
	do 
	{
		printf("%s",prompt);
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  /* get rid of newline */
		if (strlen(input) == 0)
		{
			printf("-- Please enter a value\n"); 
		} 
		else if (!isDigitString(input))
		{
			printf("-- Please enter only digits\n"); 
		} 
		else 
		{
			sscanf(input,"%d",&tempvalue);
			if ((tempvalue < min) || (tempvalue > max))
			{
				printf("-- Please enter a value between %d and %d inclusive\n",min,max); 
			}
			else
			{
				bOkValue = 1;
			}
		}
	} while (bOkValue == 0);
	return tempvalue;
}

/* Get a string no longer than a specified length, which 
 * must be all alphabetic characters. Note that the maximum
 * length that this function can handle is 255 characters.
 * prompt - Message to print to ask the user for the value
 * maxlength - Largest acceptable value for the integer
 * outputString - Array for returning the entered string.
 * Returns 1 if all is okay, 0 if the maxlength is too large.
 */
int getLimitedString(char* prompt, int maxlength, char * outputString)
{ 
	char input[256]; /* buffer for getting data */ 
	int bOkValue = 0;  /* Controls loop. We will loop until */
	/* bOkValue becomes true. */  
	if (maxlength > 255)
	{
		printf("This function is limited to strings no longer than 255 characters.\n");
		return 0;
	}
	/* if the maxlength is okay, then proceed to get the value */
	do 
	{
		printf("%s",prompt);
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  /* get rid of newline */
		if (strlen(input) == 0)
		{
			printf("-- Please enter a value\n"); 
		} 
		else if (!isAlphaString(input))
		{
			printf("-- Please enter only alphabetic characters\n"); 
		} 
		else if (strlen(input) > maxlength)
		{
			printf("-- Please enter a string no longer than %d characters\n",maxlength); 
		}
		else
		{
			strncpy(outputString,input,maxlength);
			bOkValue = 1;
		}
	} while (bOkValue == 0);
	return 1;
}

/* Get any string - does not have to be  all alphabetic characters,
 * but cannot be empty.
 * prompt - Message to print to ask the user for the value
 * maxlength - Maximum length of the string
 * outputString - Array for returning the entered string.
 */
void getString(char* prompt, int maxlength, char * outputString)
{ 
	char input[256]; /* buffer for getting data */ 
	int bOkValue = 0;  /* Controls loop. We will loop until */
		       /* bOkValue becomes true. */  
	do 
	{
		printf("%s",prompt);
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  /* get rid of newline */
		if (strlen(input) == 0)
		{
			printf("-- Please enter a value\n"); 
		} 
		else if (strlen(input) > maxlength)
		{
			printf("-- Please enter a string no longer than %d characters\n",maxlength); 
		}
		else
		{
			strncpy(outputString,input,maxlength);
			bOkValue = 1;
		}
	} while (bOkValue == 0);
}

/* Get a numeric string. Return the value as both
 * a string and an integer by setting elements 
 * of the passed structure.
 * prompt - Message to print to ask the user for the value
 * pValRec  - pointer to a structure whose fields
 *            we want to set
 */
void getNumericString(char* prompt, VALUE_RECORD_T * pValRec)
{
    int bDone = 0;
    while (!bDone)
	{ 
		getString(prompt,CHARMAX-1,pValRec->stringVal);
		if (isDigitString(pValRec->stringVal))
		{
			sscanf(pValRec->stringVal,"%d",&pValRec->integerVal);
			bDone = 1;
		}
		else
		{
			printf(" -- Enter digits only\n");
		}
	}
}
