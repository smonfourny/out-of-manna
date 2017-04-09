#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printParts(char *toPrint);
void printBold(char *toPrint);
int checkState(char *toPrint);
void removeEnter(char *toChange);
int getInputState(char *playerIn);
int checkTrailingSpaces(char *toCheck);
void getLastWord(char *input, char *lastWord);
void makeLowerCase(char *toChange);
void copyString(char *newString, char *oldString);
void purgeExtraChars(char *toChange);
int findRhyme(char *inWord, int startLine, int endLine);
void pickWord(int inputState);
void *pickLines(int inputState, int *lines);

void main()
{
	printf("Content-type: text/html\n\n");
        printf("<html>");
        printf("<body>");
	char playerIn[256];
	char lastWord[256];
	int linesInFile[2] = {0,0};
	int inputValidity = 0;
	int inputState;
	fgets(playerIn,255,stdin);
	//inputValidity = checkTrailingSpaces(playerIn);
	inputState = getInputState(playerIn);
	if (inputState == 0)
	{
		pickWord(inputState);

	}
	else
	{
		getLastWord(playerIn,lastWord);
		makeLowerCase(lastWord);
		purgeExtraChars(lastWord);
		pickLines(inputState, linesInFile);
		int isRhyme = findRhyme(lastWord,linesInFile[0],linesInFile[1]);
		if (isRhyme == 1)
		{
			if (inputState > 2)
			{
				printBold("You're winner!");
			}
			else {
				printBold("Good job! Here's your next line to rhyme.");
				printf("<br></br>");
				pickWord(inputState);
			}
		}
		else
		{
			printBold("That doesn't rhyme, try again. Here's your prompt:");
			printf("<br></br>");
			if (inputState == 1)
        		{
                        	printBold("I stand over the lake and cast out my rod,");
                        	printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"1O\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
                	}
                	else if (inputState == 2)
                	{
                        	printBold("The soft breeze in the mountains keeps me cool,");
                        	printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"1T\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
                	}
                	else if (inputState == 3)
                	{
                        	printBold("I arrive at the park and begin to wander,");
                        	printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"2O\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
                	}
                	else if (inputState == 4)
                	{
                        	printBold("I stare solemnly at the corner,");
                        	printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"2T\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
                	}

		}
	}
	printf("</body>");
        printf("</html>");
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

int getInputState(char *playerIn)
{
	char *pointer;

	pointer = playerIn;

	int counter = 0;

	int inputState = 0;

	while(*pointer != '\0')
	{
		if (counter < 2)
		{
			if (*pointer == 'G')
			{
				return 0;
			}
			if (*pointer == '1')
			{
				inputState++;
			}
			if (*pointer == '2')
                        {
                                inputState+=3;
                        }
			if (*pointer == '3')
                        {
                                inputState+=5;
                        }
			if (*pointer == 'T')
                        {
                                inputState++;
                        }
		}
		if (counter > 2)
		{
			playerIn[counter - 3] = *pointer;
		}
		*pointer++;
		counter++;
	}
	playerIn[counter - 3] = '\0';

	return inputState;

	

}

int checkTrailingSpaces(char *toCheck)
{
        char *pointer;

        pointer = toCheck;

        int counter = -1;

        while(*pointer != '\0')
        {
                *pointer++;
                counter++;
        }
	if(toCheck[counter] == ' ')
	{
		printParts("Please don't end your input with spaces.");
		return 0;
	}
	else
	{
		return 1;
	}
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

void printBold(char *toPrint)
{
	printf("<h1>%s</h1>",toPrint);
}

void getLastWord(char *input, char *lastWord)
{
	char *pointer;

	pointer = strrchr(input,'+');
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


int findRhyme(char *inWord, int startLine, int endLine)
{
	FILE *rhymeList;
	char *currentWord;
	char wordCopy[256];
	size_t wordSize = 256;
	ssize_t thisLine;
	int counter = 1;
	rhymeList = fopen("rhymelist.txt","r");

	while ((thisLine = getline(&currentWord,&wordSize,rhymeList)) != -1)
	{
		//Only works when you copy the word from the file to a new string
		copyString(wordCopy,currentWord);
		removeEnter(wordCopy);
		//Also remove the carriage return character
		removeEnter(wordCopy);
		if ((strcmp(wordCopy,inWord) == 0) && (counter >= startLine) && (counter <= endLine))
		{
			return 1;
		}
		counter++;
	}

	return 0;

}

void pickWord(int inputState)
{
	int picker;
	srand(time(NULL));
	picker = rand() % 2;
	if (inputState == 0)
	{
		if (picker == 0)
		{
			printBold("I stand over the lake and cast out my rod,");
			printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"1O\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
		}
		else if (picker == 1)
        	{
			printBold("The soft breeze in the mountains keeps me cool,");
			printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"1T\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
        	}
	}
	if ((inputState == 1) || (inputState == 2))
	{
		if (picker == 0)
        	{
			printBold("I arrive at the park and begin to wander,");
			printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"2O\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
        	}
		else if (picker == 1)
		{
			printBold("I stare solemnly at the corner,");
			printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"2T\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
		}
	}

}

void *pickLines(int inputState, int *lines)
{
	if (inputState == 1)
	{
		lines[0] = 2;
                lines[1] = 161;
	}
	else if (inputState == 2)
	{
		lines[0] = 164;
                lines[1] = 293;
	}
	else if (inputState == 3)
	{
                lines[0] = 296;
                lines[1] = 327;
        }
	else if (inputState == 4)
	{
                lines[0] = 330;
                lines[1] = 362;
        }
}
