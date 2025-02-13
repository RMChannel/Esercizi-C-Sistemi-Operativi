/*
Scrivere un programma C che dato un file specificato sulla linea di comando ne conta il numero di linee operando
 comesegue. Prima crea 8 sottoprocessi. Ognuno di questi provvede ad esaminare una sezione del file input pari 1/8
 della taglia totale del file. Una volta terminati tutti i figli il processo padre stamperà la somma dei valori restituiti da
 ciascun figlio. Per restituire gli 8 valori si suggerisce di usare una pipe.
 */

#include <ourhdr.h>
#define N_PROC 8
#define BUFFER_DIM 1000

void doFiglio(int writePipe,off_t file, off_t mid, int i) {
	char buffer[BUFFER_DIM]="";
	int lines=0;
	ssize_t control=read(file,buffer,BUFFER_DIM);
	if(control<0) err_sys("Read andata a puttane su processo %d\n",i);
	if(i==(N_PROC-1)) {
		for(int j=0;buffer[j]!='\0';j++) {
			if(buffer[j]=='\n') lines++;
		}
	}
	else {
		for(int j=0;j<mid;j++) {
			if(buffer[j]=='\n') lines++;
		}
	}
	write(writePipe,&lines,sizeof(int));
	close(writePipe);
}

int main(int argc, char *argv[]) {
	pid_t figlio;
	int file;
	int fd[N_PROC][2];
	if((file=open(argv[1],O_RDONLY))<0) err_sys("Il file non è stato aperto correttamente\n");
	off_t mid=lseek(file,0,SEEK_END)/8;
	for(int i=0;i<N_PROC;i++) {
		pipe(fd[i]);
		file=open(argv[1],O_RDONLY);
		for(int j=0;j<i;j++) lseek(file,mid,SEEK_CUR);
		figlio=fork();
		if(figlio==0) {
			close(fd[i][0]); //Chiudo la pipe in lettura dal lato figlio
			doFiglio(fd[i][1],file,mid,i); //Richiamo la funzione figlio
			exit(0);
		}
		else if(figlio<0) {
			err_sys("Figlio %d non è nato correttamente\n",i);
		}
		else {
			close(fd[i][1]); //Chiudo la pipe in scrittura dal lato padre
		}
	}
	int respond=0, lines=1;
	while(respond<N_PROC) {
		for(int i=0;i<N_PROC;i++) {
			int result;
			ssize_t control=read(fd[i][0],&result,sizeof(int));
			if(control>0) {
				respond++;
				lines+=result;
			}
		}
	}
	char result[10];
	sprintf(result,"%d",lines);
	write(1,result,strlen(result));
	return 0;
}
