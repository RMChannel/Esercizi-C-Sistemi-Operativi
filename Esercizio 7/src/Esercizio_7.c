/*
 ============================================================================
 Name        : Esercizio_7.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

int main(int argc, char *argv[]) {
	pid_t figlio;
	figlio=fork();
	int status;
	if(figlio==0) {
		execlp("ls","ls",argv[1],argv[2],NULL);
		exit(0);
	}
	wait(&status);
	figlio=fork();
	if(figlio==0) {
		execlp("pwd","pwd",NULL);
		exit(0);
	}
	wait(&status);
	figlio=fork();
	if(figlio==0) {
		execlp("date","date",NULL);
		exit(0);
	}
	return 0;
}
