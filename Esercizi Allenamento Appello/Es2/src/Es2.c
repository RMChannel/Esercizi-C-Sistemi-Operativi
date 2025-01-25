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

int main(void) {
	int fd=open("alfabeto.txt",O_CREAT | O_RDWR,0644);
	if(fd<0) perror("Apertura file non eseguita correttamente");
	write(fd,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",26);
	lseek(fd,0,SEEK_SET);
	char *stringa=calloc(sizeof(char),30);
	read(fd,stringa,26);
	write(1,stringa,strlen(stringa));
	close(fd);
}
