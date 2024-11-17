/*
Scrivere un programma C che crea N sotto processi in modo che il main crea il primo figlio ed ogni figlio creerà un
sotto processo. Ogni processo dopo l’avvio aspetta un numero di secondi pari alla sua posizione nella lista e stampa
il pid del padre, ed il proprio pid. Dopo termina
 */

#include <ourhdr.h>
#define N 15

void fFiglio(int n, int padre) {
	if(n<N) {
		pid_t figlio=fork();
		if(figlio<0) err_sys("Figlio %d andato a puttane",n+1);
		else if(figlio==0) {
			fFiglio(n+1,padre);
			sleep(n);
			char result[50];
			sprintf(result,"Padre: %d Figlio: %d\n",padre,getpid());
			write(1,result,strlen(result));
			exit(0);
		}
	}
}

int main(void) {
	int padre=getpid();
	fFiglio(0,padre);
	wait();
	return 0;
}

