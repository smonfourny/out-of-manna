#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printBold(char *toPrint);
int checkState(char *toPrint);
void removeEnter(char *toChange);
void plusesToSpaces(char *toChange);
void restoreCharacters(char *toChange);
int getInputState(char *playerIn);
void getLastWord(char *input, char *lastWord);
void makeLowerCase(char *toChange);
void copyString(char *newString, char *oldString);
void purgeExtraChars(char *toChange);
int findRhyme(char *inWord, int startLine, int endLine);
void printFile();
void pickWord(int inputState);
void *pickLines(int inputState, int *lines);
void newSong();
void addSongLine(char *toWrite);

void main()
{
	printf("Content-type: text/html\n\n");
        printf("<html>");
        printf("<body>");
	char playerIn[256];
	char lastWord[256];
	int linesInFile[2] = {0,0};
	int inputState;
	fgets(playerIn,255,stdin);
	plusesToSpaces(playerIn);
	restoreCharacters(playerIn);
	inputState = getInputState(playerIn);
	if (inputState == 0)
	{
		newSong();
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
			if (inputState > 4)
			{
				addSongLine(playerIn);
				printFile();
				printBold("You're winner!");
			}
			else {
				addSongLine(playerIn);
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
                        	printBold("I just can't comprehend it");
                        	printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"1O\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
                	}
                	else if (inputState == 2)
                	{
                        	printBold("I'm giving everything I've got");
                        	printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"1T\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
                	}
                	else if (inputState == 3)
                	{
                        	printBold("I won't slow down");
                        	printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"2O\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
                	}
                	else if (inputState == 4)
                	{
                        	printBold("I'll keep going on");
                        	printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"2T\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
                	}
			else if (inputState == 5)
                        {
                                printBold("So it's not up to you");
                                printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"3O\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
                        }
                        else if (inputState == 6)
                        {
                                printBold("So don't say you can't make a move");
                                printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"3T\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
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

void plusesToSpaces(char *toChange)
{
        char *pointer;

        pointer = toChange;

        int counter = 0;

        while(*pointer != '\0')
        {
		if (*pointer == '+')
		{
			toChange[counter] = ' ';
		}
                *pointer++;
                counter++;
        }
	if (*pointer == '+')
	{
		toChange[counter] = ' ';
	}

}

void restoreCharacters(char *toChange)
{
        char *pointer;

        pointer = toChange;

        int counter = 0;

        while(*pointer != '\0')
        {
                if ((*pointer == '%') && (toChange[counter+1] == '2') && (toChange[counter+2] == '7'))
                {
                        toChange[counter] = '\'';
			*pointer++;
			*pointer++;
                }
		else if ((*pointer == '%') && (toChange[counter+1] == '2') && (toChange[counter+2] == 'C'))
                {
                        toChange[counter] = ',';
                        *pointer++;
                        *pointer++;
                }
		else if (*pointer == '%')
                {
			while (*pointer == '%')
			{
                        	*pointer++;
                        	*pointer++;
				*pointer++;
			}
			toChange[counter] = *pointer;
                }
		else
		{
			toChange[counter] = *pointer;
		}
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

void printBold(char *toPrint)
{
	printf("<h1>%s</h1>",toPrint);
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

void printFile()
{

	printBold("Awesome! The song we wrote together is:");
	printf("<br></br>");
	FILE *file;
        char *currentLine;
        char lineCopy[256];
        size_t lineSize = 256;
        ssize_t thisLine;
        file = fopen("song.txt","r");

        while ((thisLine = getline(&currentLine,&lineSize,file)) != -1)
        {
                //Only works when you copy the word from the file to a new string
                copyString(lineCopy,currentLine);
		printf("%s<br></br>",lineCopy);
        }

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
			printBold("I just can't comprehend it");
			addSongLine("I just can't comprehend it");
			printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"1O\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
		}
		else if (picker == 1)
        	{
			printBold("I'm giving everything I've got");
			addSongLine("I'm giving everything I've got");
			printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"1T\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
        	}
	}
	else if ((inputState == 1) || (inputState == 2))
	{
		if (picker == 0)
        	{
			printBold("I won't slow down");
			addSongLine("I won't slow down");
			printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"2O\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
        	}
		else if (picker == 1)
		{
			printBold("I'll keep going on");
			addSongLine("I'll keep going on");
			printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"2T\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
		}
	}
	else if ((inputState == 3) || (inputState == 4))
        {
                if (picker == 0)
                {
                        printBold("So it's not up to you");
                        addSongLine("So it's not up to you");
                        printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"3O\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
                }
                else if (picker == 1)
                {
                        printBold("So don't say you can't make a move");
                        addSongLine("So don't say you can't make a move");
                        printf("<form method=\"POST\" action=\"challenge.cgi\"> Enter your rhyme: <input type=\"text\" name=\"3T\"> <input type=\"submit\" value=\"Yeah!\"> </form>");
                }
        }

}

void *pickLines(int inputState, int *lines)
{
	if (inputState == 1)
	{
		lines[0] = 2;
                lines[1] = 148;
	}
	else if (inputState == 2)
	{
		lines[0] = 151;
                lines[1] = 428;
	}
	else if (inputState == 3)
	{
                lines[0] = 431;
                lines[1] = 561;
        }
	else if (inputState == 4)
	{
                lines[0] = 564;
                lines[1] = 1114;
        }
	else if (inputState == 5)
        {
                lines[0] = 1117;
                lines[1] = 1656;
        }
        else if (inputState == 6)
        {
                lines[0] = 1659;
                lines[1] = 1688;
        }
}

void newSong()
{
	FILE *file;
	char emptyString[1];
	emptyString[0] = '\0';
	file = fopen("song.txt","w");
	fprintf(file,"%s",emptyString);
	fclose(file);
}

void addSongLine(char *toWrite)
{
	FILE *file;
        file = fopen("song.txt","a");
        fprintf(file,"%s\n",toWrite);
        fclose(file);
}
