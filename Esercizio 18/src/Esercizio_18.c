/*
 ============================================================================
 Name        : Esercizio_18.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

int main(void) {
	for(long int i=0;i<100000;i++) {
		char str[100]="";
		sprintf(str,"test/file%ld.txt",i);
		int fd=open(str,O_CREAT);
	}
}
