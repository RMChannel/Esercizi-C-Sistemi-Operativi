/*
 ============================================================================
 Name        : Es4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>
#include <sys/wait.h>



int global=0;

void figlio1() {
	global=5+5;
	char stringa[100]="";
	sprintf(stringa,"PID: %d risultato: %d        FIGLIO 1\n",getpid(),global);
	write(1,stringa,strlen(stringa));
}

void figlio2() {
	global*=10;
	char stringa[100]="";
	sprintf(stringa,"PID: %d risultato: %d        FIGLIO 2\n",getpid(),global);
	write(1,stringa,strlen(stringa));
}

int main(void) {
	pid_t figlio=fork();
	if(figlio==0) { //Figlio1
		figlio1();
		exit(0);
	}
	else if(figlio<0) {
		perror("Creazione figlio 1 non andata a buon fine");
	}
	wait(0); //Qui sono sicuro di essere nel padre visto che il figlio termina con exit
	figlio=fork();
	if(figlio==0) { //Figlio2
		figlio2();
		exit(0);
	}
	else if(figlio<0) {
		perror("Creazione figlio 2 non andata a buon fine");
	}
	wait(0);
	write(1,"FINE",4);
}
