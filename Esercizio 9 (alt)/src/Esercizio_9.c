/*
 ============================================================================
 Name        : Esercizio_9.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>
#define N_PROC 2000
#define INIZIO 1
#define FINE 200

char *ctoint(int n) {
	char *s=malloc(sizeof(char)*50);
	int cifre=0, temp=n;
	while(temp>0) {
		temp/=10;
		cifre++;
	}
	s[cifre]='\0';
	while(n>0) {
		temp=n%10;
		n/=10;
		s[cifre-1]='0'+temp;
		cifre--;
	}
	return s;
}

char *convert(char *initial, int n) {
	char *s=malloc(sizeof(char)*50);
	char *sTemp=s;
	while(*initial) {
		(*s)=(*initial);
		s++;
		initial++;
	}
	char *ntos=ctoint(n);
	char *temp=ntos;
	while(*ntos) {
		(*s)=(*ntos);
		s++;
		ntos++;
	}
	(*s)='\n';
	s++;
	(*s)='\0';
	free(temp);
	return sTemp;
}

char *printNumbers(int *data) {
	char *s=malloc(sizeof(char)*2000);
	char *sTemp=s;
	for(int i=0;i<FINE;i++) {
		char *ntos=ctoint(data[i]);
		char *temp=ntos;
		while(*ntos) {
			(*s)=(*ntos);
			s++;
			ntos++;
		}
		free(temp);
		(*s)=' ';
		s++;
	}
	(*s)='\n';
	s++;
	(*s)='\0';
	return sTemp;
}

int myStrLen(char *s) {
	int n=0;
	while(*s) {
		s++;
		n++;
	}
	return n;
}

int main(void) {
	int status;
	for(int i=0;i<N_PROC;i++) {
		pid_t figlio;
		figlio=fork();
		if(figlio==0) {
			int data[50]={0};
			for(int j=INIZIO;j<=FINE;j++) data[j-1]=i*j;
			char *stampa=convert("Il mio pid è: ",getpid());
			write(1,stampa,myStrLen(stampa));
			free(stampa);
			stampa=printNumbers(data);
			write(1,stampa,myStrLen(stampa));
			free(stampa);
			exit(0);
		}
		else if(figlio<0) {
			err_sys("Figlio non andato a buon fine\n");
		}
	}
	wait(&status);
	return 0;
}
