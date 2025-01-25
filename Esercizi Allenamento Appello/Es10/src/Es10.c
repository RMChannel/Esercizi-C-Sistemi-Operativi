/*
 ============================================================================
 Name        : Es10.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

#define MAXLEN 100

void removeVocali(char *buf, char *msg) {
	while(*buf) {
		if((*buf)!='a' && (*buf)!='e' && (*buf)!='i' && (*buf)!='o' && (*buf)!='u' && (*buf)!='A' && (*buf)!='E' && (*buf)!='I' && (*buf)!='O' && (*buf)!='U') {
			(*msg)=(*buf);
			msg++;
		}
		buf++;
	}
	(*msg)='\0';
}

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
			char result[MAXLEN]="";
			removeVocali(line,result);
			write(fd2[1],result,MAXLEN);
		}
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
}
