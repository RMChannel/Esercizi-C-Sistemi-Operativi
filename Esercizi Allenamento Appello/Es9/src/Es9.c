/*
 ============================================================================
 Name        : Es9.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>
#include <sys/wait.h>

#define MAXLEN 100
#define MYNAME "Aleksandre"

int main(void) {
	int fd1[2];
	int fd2[2];
	if(pipe(fd1)<0) err_sys("Pipe 1 non creata con successo");
	if(pipe(fd2)<0) err_sys("Pipe 2 non creata con successo");
	pid_t figlio=fork();
	if(figlio<0) err_sys("Figlio non creato correttamente");
	else if(figlio==0) {
		close(fd1[1]);
		close(fd2[0]);
		FILE *fd=fdopen(fd1[0],"r");
		if(fd==NULL) err_sys("Apertura pipe in lettura non andata a buon fine");
		char line[MAXLEN]="";
		while(fgets(line,MAXLEN,fd)!=NULL) {
			line[strcspn(line,"\n")]=0;
			if(strcmp(line,MYNAME)==0) {
				if(write(fd2[1],"FOUND\n",7)<0) err_sys("Write del risultato corretto non andato a buon fine");
			}
			else {
				if(write(fd2[1],"NOT FOUND\n",11)<0) err_sys("Write del risultato corretto non andato a buon fine");
			}
		}
		close(fd2[1]);
		close(fd1[0]);
		exit(0);
	}
	else {
		close(fd1[0]);
		close(fd2[1]);
		FILE *file=fopen("file.txt","r");
		if(!file) err_sys("Apertura file non eseguita correttamente");
		char line[MAXLEN]="";
		while(fgets(line,sizeof(line),file)!=NULL) {
			if(write(fd1[1],line,strlen(line))<0) err_sys("Write non andata a buon fine");
			if(read(fd2[0],line,MAXLEN)<0) err_sys("Lettura non andata a buon fine");
			write(1,line,strlen(line));
		}
		close(fd1[0]);
		close(fd2[1]);
	}
	wait(0);
	return 0;
}
