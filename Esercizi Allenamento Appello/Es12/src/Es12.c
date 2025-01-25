/*
 ============================================================================
 Name        : Es12.c
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

#define N 100000

void figlioF(int write_pipe, int value, int fd) {
	int *n=malloc(sizeof(int));
	int *i=calloc(sizeof(int),1);
	while(read(fd,n,sizeof(int))>0) {
		if(((*n)%value)==0) {
			write(write_pipe,i,sizeof(int));
		}
		(*i)++;
	}
}

int main(void) {
	int fd=open("file.txt",O_CREAT | O_RDWR,0644);
	srand(time(NULL));
	int *n=malloc(sizeof(int));
	for(int i=0;i<N;i++) {
		*(n)=rand();
		write(fd,n,sizeof(int));
	}
	lseek(fd,0,SEEK_SET);
	int piponi[4][2];
	int divisori[]={991,1117,2221,3323};
	for(int i=0;i<4;i++) {
		if(pipe2(piponi[i], O_NONBLOCK)<0) perror("Pipe andata a puttane");
		pid_t figlio=fork();
		if(figlio<0) perror("Figlio andato a puttane");
		else if(figlio==0) {
			close(piponi[i][0]);
			figlioF(piponi[i][1],divisori[i],fd);
			exit(0);
		}
		else {
			close(piponi[i][1]);
		}
	}
	wait(0);
	size_t result;
	char stampa[30]="";
	int controls[]={0,0,0,0};
	while(1) {
		int control=1;
		for(int i=0;i<4;i++) {
			if(controls[i]) continue;
			result=read(piponi[i][0],n,sizeof(int));
			if(result==0) controls[i]=1;
			else if(result<0) perror("Read andata a fanculo");
			else {
				control=0;
				sprintf(stampa,"N %d trovato con figlio %d\n",*n,i+1);
				write(1,stampa,strlen(stampa));
			}
		}
		if(control) break;
	}
	return 0;
}
