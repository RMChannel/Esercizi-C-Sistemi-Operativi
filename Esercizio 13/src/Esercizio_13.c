/*
 ============================================================================
 Name        : Esercizio_13.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

int leggiFile(int d, int scriviPadre, int figlio) {
	int fd=open("output.txt", O_RDWR);
	int n=0, count=1;
	while(1) {
		ssize_t control=read(fd,&n,sizeof(int));
		if(control<=0) break;
		if((n%d)==0) {
			char buffer[50]="";
			sprintf(buffer,"%d %d %d",n,count,figlio);
			write(scriviPadre,buffer,sizeof(buffer));
		}
		count++;
	}
}

int main(void) {
	//Scrittura nel file
	int fd=open("output.txt",O_CREAT | O_RDWR,0644);
	int n;
	srand(time(NULL));
	for(int count=0;count<100000;count++) {
		n=rand()%100000;
		write(fd,&n,sizeof(int));
	}
	close(fd);
	//Creo la pipe
	int tubo[2];
	if(pipe2(tubo,O_NONBLOCK)==-1) err_sys("La pipe è del Molise\n");
	pid_t figlio1, figlio2, figlio3, figlio4;
	figlio1=fork();
	figlio2=fork();
	figlio3=fork();
	figlio4=fork();
	if(figlio1==0) {
		close(tubo[0]);
		leggiFile(991,tubo[1],1);
	}
	else if(figlio2==0) {
		close(tubo[0]);
		leggiFile(1117,tubo[1],2);
	}
	else if(figlio3==0) {
		close(tubo[0]);
		leggiFile(2221,tubo[1],3);
	}
	else if(figlio4==0) {
		close(tubo[0]);
		leggiFile(3323,tubo[1],4);
	}
	else {
		close(tubo[1]);
		char buffer[50];
		while(1) {
			ssize_t control=read(tubo[0],buffer,sizeof(buffer));
			if(control==0) break;
			else if(control>0) {
				printf("Numero, posizione numero e figlio: %s\n",buffer);
			}
		}
	}
}
