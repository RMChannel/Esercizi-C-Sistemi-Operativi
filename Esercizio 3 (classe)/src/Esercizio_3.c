/*
 ============================================================================
 Name        : Creazione.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>


int glob=10;
int main(void) {
	int var=100;
	pid_t pippo;
	printf("Prima della fork");
	pippo=fork();
	if(pippo==0) {
		glob++;
		var++;
	}
	else sleep(2);
	printf("pid=%d, glob=%d, var=%d\n",getpid(),glob,var);
	exit(0);
}
