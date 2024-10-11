/*
 ============================================================================
 Name        : Esercizio_6.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

void controlloFiglio(int n, int status) {
	if(WIFEXITED(status))  printf("Figlio %d, ritorno normale stato: %d\n",n,WEXITSTATUS(status));
	else if (WIFSIGNALED(status)) printf("Figlio %d, ritorno errato stato: %d\n",n,WTERMSIG(status));
}

int main(void) {
	pid_t figlio;
	figlio=fork();
	int status;
	if(figlio==0) {
		exit(3);
	}
	else {
		wait(&status);
		controlloFiglio(1,status);
		figlio=fork();
		if(figlio==0) {
			int *n;
			(*n)=3;
			exit(1);
		}
		else {
			wait(&status);
			controlloFiglio(2,status);
			figlio=fork();
			if(figlio==0) {
				sleep(1);
				exit(2);
			}
			else {
				wait(&status);
				controlloFiglio(3,status);
			}
		}
	}
}
