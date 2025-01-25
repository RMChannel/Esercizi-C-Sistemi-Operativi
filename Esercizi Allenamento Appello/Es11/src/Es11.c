/*
 ============================================================================
 Name        : Es11.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//#include <ourhdr.h>
#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>


#define N 10

void figlioF(int read_pipe, int write_pipe) {
	int *n=malloc(sizeof(int));
	while(1) {
		size_t control=read(read_pipe,n,sizeof(int));
		if(control>0) {
			(*n)*=2;
			write(write_pipe,n,sizeof(int));
		}
		else if(control==0) {
			return;
		}
	}
}

void padre(int read_pipe, int write_pipe) {
	int *n=malloc(sizeof(int));
	char result[20]="";
	for(int i=0;i<N;i++) {
		*(n)=i;
		write(write_pipe,n,sizeof(int));
	}
	close(write_pipe);
	while(1) {
		size_t control=read(read_pipe,n,sizeof(int));
		if(control==-1) continue;
		else if(control>0) {
			sprintf(result,"%d\n",*n);
			write(1,result,strlen(result));
		}
		else if(control==0) {
			return;
		}
	}
}

int main(void) {
	int fd1[2];
	int fd2[2];
	if(pipe2(fd1,O_NONBLOCK)<0) perror("1°Pipe andata a puttane");
	if(pipe2(fd2,O_NONBLOCK)<0) perror("2°Pipe andata a puttane");
	pid_t figlio=fork();
	if(figlio==0) { //Figlio
		close(fd1[1]);
		close(fd2[0]);
		figlioF(fd1[0],fd2[1]);
		close(fd1[0]);
		close(fd2[1]);
		exit(0);
	}
	else if(figlio<0) {
		perror("Creazione figlio non andata a buon fine");
	}
	else { //Padre
		close(fd1[0]);
		close(fd2[1]);
		padre(fd2[0],fd1[1]);
		close(fd2[0]);
	}
}
