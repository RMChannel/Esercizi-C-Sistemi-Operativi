/*
 Scrivere un programma C che crea 4 figli (denominati P 1 ,P 2 ,P 3 e P 4 ). Successivamente il processo padre genererà
 10.000 interi casuali e li invierà uno alla volta a ciascuno dei figli tramite una pipe dedicata (separati da una pausa
 di 10 msec.). Ogni figlio ricevuto l’intero x verificherà se questo è divisibile per un intero (37 il processo P 1 , 61 P 2 ,
 89 P 3e107 P4)eseil numero risulta divisibile scriverà nel file “multipli.txt” il messaggio: “x è divisibile per y” (x è
 l’intero ricevuto y è il divisore). Una volta chiusa la pipe il processo figlio terminerà.
 */

#include <ourhdr.h>
#define NNUMBERS 10000

void fFiglio(int n, int file, int writePipe) {
	int r;
	while(1) {
		ssize_t control=read(writePipe,&r,sizeof(int));
		if(control==0) {
			write(1,"Ciaone",7);
			break;
		}
		else if(control>0) {
			if((r%n)==0) {
				char result[100];
				sprintf(result,"%d è divisibile per %d\n",r,n);
				write(file,result,strlen(result));
			}
		}
		else {
			err_sys("Pipe, really? Bruh");
		}
	}
}

int main(void) {
	int fd[4][2];
	int file=open("multipli.txt",O_CREAT | O_WRONLY, 0644);
	int numbers[4]={37,61,89,107};
	for(int i=0;i<4;i++) {
		pipe(fd[i]);
		pid_t figlio=fork();
		if(figlio<0) err_sys("A quanto pare non voleva nascere %d",i);
		if(figlio==0) {
			fFiglio(numbers[i],file,fd[i][0]);
			close(fd[i][1]);
			exit(0);
		}
		else {
			close(fd[i][0]);
		}
	}
	srand(time(NULL));
	for(int i=0, r;i<NNUMBERS;i++) {
		r=rand();
		for(int j=0;j<4;j++) {
			ssize_t control=write(fd[j][1],&r,sizeof(int));
			if(control<0) err_sys("Now what's wrong with her now?");
			sleep(0.1);
		}
	}
	for(int i=0;i<4;i++) close(fd[i][1]);
}
