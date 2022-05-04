#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Reading and writing end of the pipe
#define READ_END 0
#define WRITE_END 1

int main(int argc, char **argv)
{

	/*************************************** command line arguments ***************************************
		To compile assignment2.c: gcc assignment2.c -o assignment2
		To run your program: ./assignment2 "CS" "3305" " is fun!"
		argv[0] = "./assignment2"
		argv[1] = "CS"
		argv[2] = "3305"
		argv[3] = " is fun!"

		Number of arguments (argc) = 4

		In this assignment, the parent process reads argv[1] and the child process reads argv[2] and argv[3]
		e.g. In the parent process: char *x = argv[1];
	*******************************************************************************************************/

	// If the user does not pass X, Y and Z, the program will terminate
	if (argc != 4)
	{
		printf("Invalid arguments\n");
		exit(0);
	}

	// You must insert the following into your code (Replace zeros with the appropriate values/variables)

	// Note: You do not need to implement a function to concatenate two strings. "string.h" header file has been included



	/***************************************************************************************************
	 * 										   YOUR CODE GOES HERE										
	 ***************************************************************************************************/
	int port[2];
	
	if(pipe(port)<0)
	{
		perror("pipe");
	}
	else
	{
		printf("A pipe is created for communication between parent (PID %d) and child\n", getpid());
		pid_t pid = fork();	
		if(pid<0)
		{
			perror("fork error");
		}
		else if(pid==0)
		{
			printf("parent (PID %d) created a child (PID %d)\n", getppid(), getpid());
			printf("parent (PID %d) receives X = \"%s\" from the user\n", getppid(), argv[1]);
			printf("child (PID %d) receives Y = \"%s\" and Z = \"%s\" from the user\n", getpid(), argv[2], argv[3]);
			char *content = strcat(argv[2], argv[3]);
			int offset = strlen(content);
			printf("child (PID %d) concatenates Y and Z to generate Y'= %s\n", getpid(), content);
			write(port[WRITE_END], content, offset);
			printf("child (PID %d) writes Y' into the pipe\n", getpid());
			exit(0);
		}
		else
		{
			int t = wait(NULL);
			char *final = argv[1];
			int readlength = strlen(strcat(argv[2], argv[3]));
			char *suf = malloc(sizeof(char)*readlength);
			int s = read(port[READ_END], suf, readlength);
			printf("parent (PID %d) reads Y' from the pipe (Y' = \"%s\")\n", getpid(), suf);
			strcat(final, suf);
			printf("parent (PID %d) concatenates X and Y' to generate the string: %s\n", getpid(), final);
		}
	}
	return 0;
}
