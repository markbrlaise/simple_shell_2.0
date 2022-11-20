#include "main.h"

int main()
{
	char inputString[MAXCOM], *parsedArgs[MAXLIST];
	char *parsedArgsPiped[MAXLIST];
	int execflag;
	
	init_shell();
	while (1)
	{
		//print prompt
		//printf("\n$ "); 
		if (takeInput(inputString))//read input
			continue;

		execflag = processString(inputString, parsedArgs, parsedArgsPiped);
		//parse the input
		//0 if command is not found or an inbuilt command
		//1 if no pipes are found
		//2 if pipes are present
	
		if (execflag == 1)
			execArgs(parsedArgs);
			//execve normally
		if (execflag == 2)
			execArgsPiped(parsedArgs, parsedArgsPiped);
			// execve with pipes
	}
	return (0);
}
