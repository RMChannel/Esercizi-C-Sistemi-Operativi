/*
 ============================================================================
 Name        : Esercizio_9.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>
#define N_PROC 500
#define INIZIO 1
#define FINE 50

int main(void) {
	int status;
	for(int i=0;i<N_PROC;i++) {
		pid_t figlio;
		figlio=fork();
		if(figlio==0) {
			int data[50]={0};
			for(int j=INIZIO;j<=FINE;j++) data[j-1]=i*j;
			printf("Il mio pid è: %d %d\n",getpid(),i);
			for(int j=INIZIO;j<=FINE;j++) printf("%d ",data[j-1]);
			printf("\n");
			exit(0);
		}
	}
	wait(&status);
	return 0;
}
