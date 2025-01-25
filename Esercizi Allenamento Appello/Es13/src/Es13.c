/*
 ============================================================================
 Name        : Es13.c
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
	int fd1=open("output1.txt",O_CREAT | O_WRONLY,0644);
	int fd2=open("output2.txt",O_CREAT | O_WRONLY,0644);
	char *c=malloc(sizeof(char));
	while(1) {
		if(read(read_pipe,c,sizeof(char))==0) return;
		write(fd1,c,sizeof(char));
		write(fd2,c,sizeof(char));
	}
}

int main(void) {
	int fd[2];
	if(pipe2(fd,O_NONBLOCK)<0) perror("Qualcosa non va con la pipe");
	pid_t figlio=fork();
	if(figlio<0) perror("Figlio andato a puttane");
	else if(figlio==0) {
		close(fd[1]);
		figlioF(fd[0]);
		exit(0);
	}
	else {
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",NULL);
	}
}
