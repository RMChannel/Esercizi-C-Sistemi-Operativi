/*
 ============================================================================
 Name        : Esercizio_15.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

int main(void) {
	int fd[2];
	pipe2(fd);
	pid_t figlio=fork();
	if (figlio==0) {
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		char buffer[100];
		read(STDIN_FILENO, buffer, sizeof(buffer));
		write(STDOUT_FILENO,buffer,sizeof(buffer));
	}
	else {
		close(fd[0]);
		char output[]="Buongiorno";
		write(fd[1],output,strlen(output));
	}
	return 0;
}
