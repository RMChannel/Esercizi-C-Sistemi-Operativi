/*
 ============================================================================
 Name        : Es6.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

void figlio1(int argc, char *argv[]) {
	for(int i=1;i<argc;i++) {
		execlp("ls","ls",argv[i]);
	}
}

void figlio2() {
	execlp("pwd","pwd");
}

void figlio3() {
	execlp("date","date");
}

int main(int argc, char *argv[]) {
	pid_t figlio=fork();
	if(figlio<0) perror("Il figlio 1 non è stato creato correttamente");
	else if(figlio==0) {
		figlio1(argc,argv);
		exit(0);
	}
	figlio=fork();
	if(figlio<0) perror("Il figlio 2 non è stato creato correttamente");
	else if(figlio==0) {
		figlio2();
		exit(0);
	}
	figlio=fork();
	if(figlio<0) perror("Il figlio 3 non è stato creato correttamente");
	else if(figlio==0) {
		figlio3();
		exit(0);
	}
	return 0;
}
