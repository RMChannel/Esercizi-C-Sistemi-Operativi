/*
Scrivere un programma C che crea n sotto processi. Il processo main provvederà alla creazione degli N processi figli.
Ogni processo dopo l’avvio aspetta un numero di secondi pari alla sua posizione nela lista e stampa il pid del padre,
ed il proprio pid. Dopo termina
 */

#include <ourhdr.h>
#define N 15

int main(void) {
	int padre=getpid();
	for(int i=0;i<N;i++) {
		pid_t figlio=fork();
		if(figlio<0) err_sys("Figlio %d andato a puttane",i+1);
		else if(figlio==0) {
			int pidFiglio=getpid();
			sleep(i);
			char result[50];
			sprintf(result,"Padre: %d Figlio: %d\n",padre,pidFiglio);
			write(1,result,strlen(result));
			exit(0);
		}
	}
	wait();
	return 0;
}
