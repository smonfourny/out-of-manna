#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void parseInput(char *, char*); // Function prototype to parse given input

int main(){
  int n = atoi(getenv("CONTENT_LENGTH")); // Get length of input
  char* in1 = (char*)malloc(45); // Malloc a pointer to store input
  char* in2 = (char*)malloc(15); // For 2nd input value, will be tokenized
  fgets(in1,n+1,stdin); // Get input from stdin (POST)
  // Tokenize input, will make in1 everything before & and in2 everything after
  strtok_r(in1, "&", &in2);
  // Check which string is command and which is the orientation, then parse accordingly
  //parseInput(in1,in2);
  if(strncmp(in1,"command" , 7)==0){ // If in1 starts with command
    parseInput(in1, in2); // Call function to parse input, with in1 as command
  }
  else{ // Else in2 has command and in1 has orientation
    parseInput(in2,in1);
    }
  free(in1); // Free allocated memory
  free(in2);
  return 0; // Successfully finished
}

void parseInput(char* command, char* orient){
  printf("Content-type: text/html\n\n"); // Display HTML
  printf("<html\n>\n");
  printf("<meta http-equiv=\"refresh\" content=\"0; url=http://cs.mcgill.ca/~jlore\" >/ \n"); // Redirect website
  printf("<body>\n"); // Opening tags
  //printf("%s %s",command, orient);
  printf("</body>\n"
	 "</html>\n"); // Closing tags
}
