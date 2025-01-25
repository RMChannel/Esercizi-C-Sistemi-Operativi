/*
 ============================================================================
 Name        : Es3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

int main(void) {
	pid_t figlio=fork();
	char stringa[100]="";
	if(figlio==0) {
		sprintf(stringa,"Io sono il figlio %d\n",getpid());
		write(1,stringa,strlen(stringa));
		exit(0);
	}
	else if(figlio<0) {
		perror("Creazione figlio non andata a buon fine");
	}
	else {
		sprintf(stringa,"Io sono il padre %d\n",getpid());
		write(1,stringa,strlen(stringa));
	}
	return 0;
}
