#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printParts(char *toPrint);
void removeEnter(char *toChange);
void getLastWord(char *input, char *lastWord);
void makeLowerCase(char *toChange);
void copyString(char *newString, char *oldString);
void purgeExtraChars(char *toChange);

void main()
{
	char playerIn[256];
	char lastWord[256];
	printf("Give a string to print.\n");
	fgets(playerIn,255,stdin);
	removeEnter(playerIn);
	printParts(playerIn);
	getLastWord(playerIn,lastWord);
	printParts(lastWord);
	makeLowerCase(lastWord);
	printParts(lastWord);
	purgeExtraChars(lastWord);
	printParts(lastWord);

}

void removeEnter(char *toChange)
{
	char *pointer;

	pointer = toChange;

	int counter = -1;
	
	while(*pointer != '\0')
	{
		*pointer++;
		counter++;
	}
	toChange[counter] = '\0';
}

void printParts(char *toPrint)
{
        char *pointer;
	struct timespec waitTime;
	waitTime.tv_sec = 0;
	waitTime.tv_nsec = 75000000;

        pointer = toPrint;

        while(*pointer != '\0')
        {
		printf("%c",*pointer);
		fflush(stdout);
		nanosleep(&waitTime, NULL);
                *pointer++;
        }
	printf("\n");
}

void getLastWord(char *input, char *lastWord)
{
	char *pointer;

	pointer = strrchr(input,' ');
	if (!pointer)
	{
		copyString(lastWord,input);
	}
	else
	{
		*pointer++;

		int counter = 0;

		while(*pointer != '\0')
        	{
			lastWord[counter] = *pointer;
			*pointer++;
			counter++;
	        }
		lastWord[counter] = '\0';
	}
}

void makeLowerCase(char *toChange)
{
	char *pointer;

	pointer = toChange;

	int counter = 0;

	while(*pointer != '\0')
	{
		if((*pointer >= 'A') && (*pointer <= 'Z'))
		{
			toChange[counter] = toChange[counter] + 32;
		}

		*pointer++;
		counter++;

	}

}

void copyString(char *newString, char *oldString)
{
        char *pointer;

        pointer = oldString;

        int counter = 0;

        while(*pointer != '\0')
        {
		newString[counter] = *pointer;
                *pointer++;
                counter++;
        }
	newString[counter] = '\0';
}

void purgeExtraChars(char *toChange)
{
	char *pointer;
	char newString[256];

	pointer = toChange;

	int counter = 0;

	while(*pointer != '\0')
	{
		if(((*pointer >= 'a') && (*pointer <= 'z')) || (*pointer == '-') || (*pointer == '\''))
		{
			newString[counter] = *pointer;
		}
		else
		{
			counter--;
		}
		*pointer++;
		counter++;

	}
	newString[counter] = '\0';

	copyString(toChange,newString);

}
