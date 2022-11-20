#include "main.h"

void init_shell()
{
	clear();
	printf("\n\n\n\n********************************");
	printf("\n\n\n\t**********MEIN SHELL************");
	printf("\n\n\n\t-AT YOUR OWN RISK BRUV-");
	printf("\n\n\n\n********************************");
	char *username = getenv("USER");
	printf("\n\n\nHey @%s", username);
	sleep(1);
	clear();
}

int takeInput(char *str)
{
	char *buf = malloc(MAXCOM);
	size_t len = MAXCOM;

	printf("\n$ ");
	getline(&buf, &len, stdin);
	if (strlen(buf) != 0)
	{
		//add_history(buf);
		strcpy(str, buf);
		return (0);
	}
	else
		return (1);
}

void execArgsPiped(char **parsed, char **parsedpipe)
{
	//0 is read end, 1 is write end
	int pipefd[2];
	pid_t p1, p2;

	if (pipe(pipefd) == -1)
	{
		printf("\nPipe could not be initialized\n");
		return;
	}
	p1 = fork();
	if (p1 < 0)
	{
		printf("\nCould not fork child\n");
		return;
	}
	if (p1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCouldnot execute command... 1\n");
			exit(0);
		}
	}
	else
	{
		p2 = fork();

		if (p2 < 0)
		{
			printf("\nFailed to fork child");
			exit(0);
		}
		if (p2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execvp(parsedpipe[0], parsedpipe) < 0)
			{
				printf("\nFailed to execute command...\n");
				exit(0);
			}
		}
		else 
		{
			wait(NULL);
			wait(NULL);
		}
	}
}

//help command builtin
void openHelp()
{
	printf("\n***WELCOME TO MY SHELL HELP***"
		"\nCopyright @ mark_laiz"
		"\nPlz use shell at ur own risk..."
		"\nList of commands supported:"
		"\n>cd"
		"\n>help"
		"\n>exit"
		"\n>hola"
		"\n>plus all other general commands available in UNIX shell"
		"\n>pipe handling"
		"\n>improper space handling");
}

void execArgs(char **parsed)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		printf("Failed to fork child\n");
		return;
	}
	else if(pid == 0)
	{
		if (execvp(parsed[0], parsed) < 0)
			printf("Failed to execute command");
		exit(0);
	}
	else {
		wait(NULL);
		return;
	}
}

int ownCmdHandler(char **parsed)
{
	int switchOwnArg = 0;
	int i;
	char *ListOfOwnCmds[4];
	char *username;
	char *helper = parsed[0];

	ListOfOwnCmds[0] = "exit";
	ListOfOwnCmds[1] = "cd";
	ListOfOwnCmds[2] = "help";
	ListOfOwnCmds[3] = "hola";
	
	//printf("\nhere we are!");

	//printf("%ld\n", strlen(helper));
	//printf("%ld\n", strlen(ListOfOwnCmds[3]));

	for (i = 0; i < 4; ++i)
	{
		//printf("\n%d", strcmp(parsed[0], ListOfOwnCmds[i]));
		if(_strcmp(ListOfOwnCmds[i], parsed[i]) == 0)
		{
			switchOwnArg = i + 1;
			//printf("\n passed!");
			break;
		}
		//printf("\n%s == ", parsed[0]);
		//printf("%s", ListOfOwnCmds[i]);
	}

	switch (switchOwnArg)
	{
		case 1:
			printf("\nTschao !!");
			exit(0);
		case 2:
			chdir(parsed[1]);
			return (1);
		case 3:
			openHelp();
			return (1);
		case 4:
			username = getenv("USER");
			//printf("\nsth wrong!!");
			printf("Feel at home %s\nI am ur good friend... Worry not", username);
			return (1);
		default:
			break;
	}
	return (0);
}

int parsePipe(char *str, char **strpiped)
{
	int i;
	for (i = 0; i < 2; ++i)
	{
		strpiped[i] = strsep(&str, "|");
		if (strpiped[i] == NULL)
			break;
	}
	if (strpiped[1] == NULL)
		return (0);
	else
		return (1);
}

void parseSpace(char *str, char **parsed)
{
	int i;

	for (i = 0; i < MAXLIST; ++i)
	{
		parsed[i] = strtok(str, " ");
		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) == 0)
			--i;
	}
	//printf("\n%s", parsed[0]);
	//printf("\ndone !");
}

int processString(char *str, char **parsed, char **parsedpipe)
{
	char *strpiped[2];
	int piped = 0;

	piped = parsePipe(str, strpiped);
	if (piped)
	{
		//printf("yep");
		parseSpace(strpiped[0], parsed);
		parseSpace(strpiped[1], parsedpipe);
	}
	else
	{
		//printf("no pipe");
		parseSpace(str, parsed);
		//printf("\n%s", parsed[0]);
		if (ownCmdHandler(parsed))
		{
			//printf("builtin having issues");
			return (0);
		}
		else
		{
			//printf("\ncmd handler having issues");
			//printf("\n%d", (piped + 1));
			return (piped + 1);
		}
	}
}
