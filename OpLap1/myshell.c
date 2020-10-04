#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

// Parent will wirte and child will read from the pipe
#define READ 0
#define WRITE 1

#define MAX_LENGTH 1024

// Clearing the shell using escape sequences
// \033 stands for ESC
// \033[H moves the cursor to the top left corner of the screen
// \033[J clears the part of the screen from the cursor to the end of the screen
#define clear() printf("\033[H\033[J")


// Define method
void type_prompt();
// void read_command();
void mySystem(char *command);
void execPipe(char **command1, char **command2);
int splitCommandIntoArray(char *command, char **splitCommand);

// Define constant variables
const size_t MaxLine = 1024;
const size_t MaxSplitCommand = 10;

int main(void) {
	char command[MaxLine];
	char *splitCommand[MaxSplitCommand];
	int i, j, k = 0;
	int flag = 1; // Check if there is pipe
	clear();
	while (1) {
		type_prompt();
		// fgets(): Gets a line from standard in where user type e.g., ls
		if (fgets(command, MaxLine, stdin) == NULL) {
			break;
		}
 		command[strlen(command) - 1] = '\0'; // Overwrite '\n' I mean remove \n from command
		// Exit the program when user type exit
                if (strcmp (command, "exit") == 0) {
                	 exit(0); // berak;
                }


		// Check for pipe
		for (i = 0; i <  strlen(command); i++) {
			if (command[i] == '|') {
				printf("%s\n", "Pipe Found");
				flag = 0;
				break;
			}
		}

		if (flag == 0) { // The command has pipe
		    // Split the command
		    // E.g., ls -l | grep l
		    // argv1 will has ls -l
		    // argv2 will has grep l
			int lengthOfSplitCommand = splitCommandIntoArray(command, splitCommand);
			char *argv1[MaxSplitCommand + 1] = {0};
			char *argv2[MaxSplitCommand + 1] = {0};

			// To know the location of pipe
			for (i = 0; i < lengthOfSplitCommand; i++) {
				if (strcmp(splitCommand[i], "|") == 0) {
					break;
				}
			}

			// The command before pipe (|) will be in argv1
			for (j = 0; j < i; j++) {
			       argv1[j] = splitCommand[j];
			}

            // The command before pipe (|) will be in argv2
			for (j = i+1; j <  lengthOfSplitCommand; j++,k++) {
				argv2[k] = splitCommand[j];
			}
			// Execute pipe command
            execPipe(argv1, argv2);
		} else {
            mySystem(command);
		}
	}
	return 0;
}

void type_prompt() {
	printf("%s", "$ ");
}


/*
void read_command() {
}
*/

void mySystem(char *command) {
	pid_t pid = fork(); // Create a new process, which is called child process. Fork copies the current process
	if (pid == 0) { // Child
		// /bin/sh/ which is the shell program
		// Run with -c option which mean run the following program
		// NULL mean this is an array that has to be NULL terminated
		// command: entire argument list
		char *arguments[] = {"/bin/sh", "-c", (char *) command, NULL};
		execv(arguments[0], arguments);
	}
	waitpid(pid, NULL, 0);
}

// Split the command with pipe in array
int splitCommandIntoArray(char *command, char **splitCommand) {
	int i, lengthOfCommand=-1; // lengthOfCommand has how much command the user does input
	for (i = 0; i < MaxSplitCommand; i++) {
		splitCommand[i] = strsep(&command, " "); // Split when find a space
		lengthOfCommand++;
		if (splitCommand[i] == NULL)
			break;
	}
	return lengthOfCommand;
}


// Execute pipe command
void execPipe(char **command1, char **command2) {
    int fd[2];
    pid_t childPid;
    pipe(fd); // Passing information from one process to another


    childPid = fork();


    if (childPid == 0) { // Child
        close(fd[WRITE]); // No writing necessary
        dup2(fd[READ], 0);  // Duplicate object, create a copy of file descriptor
        close(fd[READ]);    // Already duplicated, Therefor we don't need any more
        execvp(command2[0], command2); // Execute command after pipe character
        // Child will never get to here
    } else { // Parent
        close(fd[WRITE]); // Not used
        dup2(fd[READ], 0); 
        close(fd[READ]);
        execvp(command1[0], command1); // Execute command before pipe character
    }
}

