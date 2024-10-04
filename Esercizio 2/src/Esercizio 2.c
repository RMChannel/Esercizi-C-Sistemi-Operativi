/*
 ============================================================================
 Name        : Esercizio.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

int main(void) {
	char *alfabeto="ABCDEFGHILMNOPQRSTUVZ";
	startCounting();
	int fd=open("alfabeto.txt",O_CREAT | O_RDWR,0644);
	write(fd,alfabeto,strlen(alfabeto));
	close(fd);
	stopCounting();
	printResourceUsage();
	return 0;
}
