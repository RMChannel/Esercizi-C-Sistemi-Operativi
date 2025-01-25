/*
 ============================================================================
 Name        : Es7.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include<ourhdr.h>
#include <sys/wait.h>

int main(void) {
	pid_t figlio=fork();
	if(figlio<0) perror("Figlio non creato correttamente");
	else if(figlio==0) {
		char messaggio[]="Porco dio";
		int fd=open("file.txt",O_CREAT | O_WRONLY,0644);
		write(fd,messaggio,strlen(messaggio));
		exit(0);
	}
	wait(0);
	int fd=open("file.txt",O_RDONLY);
	char result[100]="";
	read(fd,result,100);
	write(1,result,strlen(result));
	return 0;
}
