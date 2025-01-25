/*
 ============================================================================
 Name        : Es5.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>
#include <sys/wait.h>

void checkFiglio(int status) {
	if(WIFEXITED(status)) {
		printf("Figlio terminato correttamente con stato: %d\n",WEXITSTATUS(status));
	}
	else if(WIFSIGNALED(status)) {
		printf("Figlio terminato con errore: %d\n",WTERMSIG(status));
	}
}

int main(void) {
	int status;
	pid_t figlio=fork(); //1°Figlio
	if(figlio<0) perror("Creazione figlio 1 non andata a buon fine");
	else if(figlio==0) {
		exit(5);
	}
	wait(&status);
	checkFiglio(status);
	//2°Figlio
	figlio=fork();
	if(figlio<0) perror("Creazione figlio 2 non andata a buon fine");
	else if(figlio==0) {
		int *n;
		(*n)=5;
	}
	wait(&status);
	checkFiglio(status);
	figlio=fork();
	if(figlio<0) perror("Creazione figlio 3 non andata a buon fine");
	else if(figlio==0) {
		sleep(5);
		exit(10);
	}
	wait(&status);
	checkFiglio(status);
}
