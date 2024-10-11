/*
 ============================================================================
 Name        : Esercizio 4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

int main(void) {
	pid_t pippo;
	pippo=fork();
	if(pippo==0) {
		printf("Questo è il mio (figlio) pid: %d\n",getpid());
	}
	else if(pippo==-1) {
		printf("Fork andato a puttane\n");
	}
	else {
		wait();
		printf("Questo è il mio (padre) pid: %d\n",getpid());
	}
}
