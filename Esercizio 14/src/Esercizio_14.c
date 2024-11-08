/*
 ============================================================================
 Name        : Esercizio_14.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

int main(void) {
	int fd1=open("output1.txt",O_CREAT | O_RDWR,0644);
	int fd2=open("output2.txt",O_CREAT | O_RDWR,0644);
	int save=dup(STDOUT_FILENO);
	if(dup2(fd1,STDOUT_FILENO)==-1) printf("Sostituzione con file 1 non andato\n");
	write(STDOUT_FILENO,"Ciao file 1",sizeof(char)*12);
	if(dup2(fd2,STDOUT_FILENO)==-1) printf("Sostituzione con file 2 non andato\n");
	write(STDOUT_FILENO,"Ciao file 2",sizeof(char)*12);
	if(dup2(save,STDOUT_FILENO)==-1) printf("Ripristino STDOUT non andato\n");
	write(STDOUT_FILENO,"Ciao terminale",sizeof(char)*15);
}
