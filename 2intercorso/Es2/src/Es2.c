/*
 ============================================================================
 Name        : Es2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>
#define N_PROC 10
int cnt=0;

void fFiglio() {
	while(1) {
		pause();
		cnt++;
		usleep(200000);
	}
}

int main(void) {
	pid_t figli[N_PROC];
	for(int i=0;i<N_PROC;i++) {
		figli[i]=fork();
		if(figli[i]<0) err_sys("Figlio %d non andato a buon fine",i+1);
		else if(figli[i]==0) {
			fFiglio();
		}
		else {

		}
	}
}
