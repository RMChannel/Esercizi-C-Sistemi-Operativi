/*
 ============================================================================
 Name        : Es8.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>
#include <sys/wait.h>

#define N_PROC 100
#define FINE 50

void figlioF(int start) {
	for(int i=0;i<=FINE;i++) {
		char number[20];
		sprintf(number,"%d\n",start+i);
		write(1,number,strlen(number));
	}
}

int main(void) {
	pid_t figlio;
	for(int i=0;i<N_PROC;i++) {
		figlio=fork();
		if(figlio<0) err_sys("Figlio %d non creato correttamente",i);
		else if(figlio==0) {
			figlioF(i*10);
			exit(0);
		}
	}
}
