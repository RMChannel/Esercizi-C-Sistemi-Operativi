/*
 ============================================================================
 Name        : Esercizio_5.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

int global=0;
int main(void) {
	pid_t figlio;
	figlio=fork();
	if(figlio==0) {
		global+=5;
		int n2=3;
		int n3=6;
		int n4=n2+n3;
		printf("global=%d pid=%d n=%d\n",global,getpid(),n4);
		return 0;
	}
	else {
		wait();
		figlio=fork();
		if(figlio==0) {
			global+=7;
			printf("global=%d pid=%d\n",global,getpid());
		}
		else {
			wait();
			printf("Processo padre (%d) terminato\n",getpid());
		}
	}
}
