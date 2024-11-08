/*
 ============================================================================
 Name        : Esercizio_12.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

int main(void) {
	int fd1[2], fd2[2];
	pid_t figlio;
	if(pipe2(fd1,O_NONBLOCK)==-1) err_sys("Pipe 1 non andata a buon fine\n");
	if(pipe2(fd2,O_NONBLOCK)==-1) err_sys("Pipe 2 non andata a buon fine\n");
	figlio=fork();
	if(figlio==0) {
		close(fd1[1]);
		close(fd2[0]);
		int n;
		while(1) {
			ssize_t control=read(fd1[0],&n,sizeof(int));
			if(control==0) break;
			else if(control>0) {
				n*=2;
				write(fd2[1],&n,sizeof(int));
			}
		}
	}
	else if(figlio<0) err_sys("Figlio leaves the chat\n");
	else {
		close(fd1[0]);
		close(fd2[1]);
		int arr[]={1,2,3,4,5};
		for(int i=0;i<5;i++) {
			write(fd1[1],&arr[i],sizeof(int));
			int n;
			ssize_t control=read(fd2[0],&n,sizeof(int));
			while(control==-1) control=read(fd2[0],&n,sizeof(int));
			if(control==0) break;
			printf("Numero inviato: %d, numero ricevuto: %d\n",arr[i],n);
		}
		sleep(1);
	}
	return 0;
}
