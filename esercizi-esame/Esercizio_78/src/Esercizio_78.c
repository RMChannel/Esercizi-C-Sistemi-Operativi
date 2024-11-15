/*
Scrivere un programma C che dato un file specificato sulla linea di comando ne conta il numero di linee operando
 comesegue. Prima crea 8 sottoprocessi. Ognuno di questi provvede ad esaminare una sezione del file input pari 1/8
 della taglia totale del file. Una volta terminati tutti i figli il processo padre stamperà la somma dei valori restituiti da
 ciascun figlio. Per restituire gli 8 valori si suggerisce di usare una pipe.
 */

#include <ourhdr.h>
#define N_PROC 8
#define BUFFER_DIM 100

void doFiglio(int writePipe,off_t file, off_t mid) {
	char buffer[BUFFER_DIM];
	int bytes=0;
	while(bytes!=-1) {
		read(file,buffer,BUFFER_DIM);
		/*
		if((bytes+BUFFER_DIM)>mid) {
			if(read(file,buffer,mid)<0) err_sys("Lettura file non andata a buon fine");
			bytes=-1;
		}
		else {
			ssize_t control=read(file,buffer,BUFFER_DIM);
			if(control<0) err_sys("Lettura file non andata a buon fine");
			bytes+=control;
		}*/
		write(1,buffer,BUFFER_DIM);
	}
}

int main(int argc, char *argv[]) {
	pid_t figlio;
	int file;
	int fd[N_PROC][2];
	if((file=open(argv[1],O_RDONLY))<0) err_sys("Il file non è stato aperto correttamente\n");
	off_t mid=lseek(file,0,SEEK_END)/8;
	for(int i=0;i<N_PROC;i++) {
		pipe(fd[i]);
		figlio=fork();
		if(figlio==0) {
			close(fd[i][0]); //Chiudo la pipe in lettura dal lato figlio
			lseek(file,mid,SEEK_CUR);
			doFiglio(fd[i][1],file,mid); //Richiamo la funzione figlio
			exit(0);
		}
		else if(figlio<0) {
			err_sys("Figlio %d non è nato correttamente\n",i);
		}
		else {
			close(fd[i][1]); //Chiudo la pipe in scrittura dal lato padre
		}
	}

	return 0;
}
