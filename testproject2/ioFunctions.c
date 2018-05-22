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
#include <time.h>

#include "ioFunctions.h"

/*removeNewline function
*This function will remove newline from the buffer.
*Argument : - input - buffer string*/
void removeNewline(char *input)
{
	if(input[strlen(input) - 1] == '\n')
	{
		input[strlen(input) - 1] = '\0';	
	}
}


/*dateToday function: This function will get the present date
*					  then store the date of today into pDay,pMonth and pYear
**/
void dateToday(int* pDay, int *pMonth, int* pYear)
{
    time_t seconds = 0;    
    struct tm * pTimeStruct;

    seconds = time(&seconds);
    pTimeStruct = localtime(&seconds);
    *pDay = pTimeStruct->tm_mday;
    *pMonth = pTimeStruct->tm_mon + 1;
    *pYear = pTimeStruct->tm_year + 2443;
}

/*checkDate function: Check the input release date if the format is valid
*It return 'check' variable:	0 - if the input is not valid
*								1 - if the input is valid*/
int checkDate(char* inputDate)
{
	int tempDay = 0; 			/* to collect day that divided from inputDate */
	int tempMonth = 0;		 	/* to collect month that divided from inputDate */
	int tempYear = 0; 			/* to collect year that divided from inputDate */
	int check = 1; 				/* return value is it correct format or not */
	int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; /* to check max days in each month */
	int maxDay = 0; 			/* max day in each month */
	int i = 0; 					/* count loop */


	removeNewline(inputDate);
	if(strlen(inputDate) != 10) /* if date length is not 10 -- INVALID */
	{
		printf("INVALID FORMAT - MUST BE YYYY-MM-DD\n");
		check = 0;
	}
	else if((inputDate[4] != '-') || (inputDate[7] != '-')) /* if do not have slash '/' -- INVALID  */
	{
		printf("INVALID FORMAT - MUST BE YYYY-MM-DD\n");
		check = 0;
	}
	else 
	{
		for(i=0; (i < 10) && (check == 1) ; i++)
		{
			if(i == 4 || i == 7) /* do not interset '/' */
			{
				continue;
			}
			else if(!isdigit(inputDate[i])) /* date is digit or not */
			{
				printf("INVALID INPUT - ONLY NUMERIC VALUE\n");
				check = 0;
			}
		}
	}
	if(check == 1) 
	{
		sscanf(inputDate,"%d-%d-%d",&tempYear,&tempMonth,&tempDay); /* Collect inputDate into YYYY/MM/DD format */
		if(tempMonth < 1 || tempMonth > 12) /*Month must be within 1 to 12*/
		{
			printf("INVALID MONTH\n");
			check = 0;
		}
		else 
		{
			maxDay = monthDays[tempMonth-1]; /* collect maxDay in each month to this variable */
			if((tempMonth == 2) && (tempYear%4 == 0) && (tempYear%100 != 0)) /* if it is leap year */
			{
				maxDay = 29; /* change maxDay in February to 29 days */
			}
			if((tempDay < 1) || (tempDay > maxDay))
			{
				printf("INVALID DATE\n");
				check = 0;
			}
		}
	}

	return check;
}

/*dateCompare function: compare date input to the date today
*return 'check' value: 1 - if the input is over the date today
*					   0 - if the input is under the date today*/
int dateCompare(int day1,int month1,int year1, 
                int day2,int month2,int year2)
{
    int check = 0;

	if((day1 > day2) || (month1 > month2) || (year1 > year2))
	{
		check = 1;
		printf("INVALID DATE: Seen date cannot be in the future");
	}

    return check;
}    

/*checkSeenDate function: Check if date that the user insert is within the present or the past
*return 'check' value: 1 - if the input is over the date today
*					   0 - if the input is under the date today*/
int checkSeenDate(char* inputDate)
{
	int check = 0;
	int tempDate,tempMonth,tempYear,pDay,pMonth,pYear;
	
	dateToday(&pDay,&pMonth,&pYear);
	if(checkDate(inputDate) == 0)
	{
		sscanf(inputDate,"%d-%d-%d",&tempYear,&tempMonth,&tempDate);		/* Collect inputDate into YYYY/MM/DD format */
		check = dateCompare(tempDate,tempMonth,tempYear,pDay,pMonth,pYear);	/* Compare seen date with the date today*/		
	}
	else
	{
		check = 1;
	}
	
	return check;
}


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
