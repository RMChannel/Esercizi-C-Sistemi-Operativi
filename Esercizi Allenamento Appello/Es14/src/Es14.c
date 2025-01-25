/*
 ============================================================================
 Name        : Es14.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

void figlioF(int read_pipe) {
	dup2(read_pipe,STDIN_FILENO);
	char message[50]="";
	read(read_pipe,message,50);
	write(1,message,50);
}

int main(void) {
	int fd[2];
	if(pipe(fd)<0) perror("La pipe non è stata creata correttamente");
	pid_t figlio=fork();
	if(figlio<0) perror("Creazione figlio non andata a buon fine");
	else if(figlio==0) {
		close(fd[1]);
		figlioF(fd[0]);
		exit(0);
	}
	else {
		close(fd[0]);
		char message[]="Messaggio bello";
		write(fd[1],message,strlen(message));
	}
}
