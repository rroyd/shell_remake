#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <malloc.h>

int main() {
	char *paths = getenv("PATH");
	char *args[100];	
	char _input[300], path_with_command[1000];
	int pid = 0, cnt = 0, status = 0;
	while (WEXITSTATUS(status) != 2) {	
		if ((pid = fork()) == 0) { 
			printf("#$: ");
			fgets(_input, sizeof(_input), stdin); //all string
			char *command = strtok(_input, " "), *p; 
			char *pos = _input;
			while(pos) {
				if(*pos == '\n') {
					*pos = 0;
					break;
				}
				pos++;
			}
			while (command) 
			{
				args[cnt++] = command;
				command = strtok(NULL, " ");
			}
			
			args[cnt] = NULL;
			if(strcmp(args[0], "leave") == 0) {
				exit(2);
			}
			p = strtok(paths, ":");
			char path_with_command[1000];
			while(p) {
				strcpy(path_with_command, p);
				strcat(path_with_command, "/");
				strcat(path_with_command, args[0]);
				execv(path_with_command, args);
				p = strtok(NULL, ":");
			}		
	}
		else {
			wait(&status);
		}
	}
	return 0;
}
