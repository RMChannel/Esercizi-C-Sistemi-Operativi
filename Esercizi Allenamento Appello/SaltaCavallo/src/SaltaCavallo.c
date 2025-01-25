/*
 ============================================================================
 Name        : TestCorsaDeiCavalli.c
 Author      : Pippo Cattaneo
 Version     :
 Copyright   : Open Source
 Description : Hello World in C, Ansi-style
 ============================================================================

 Scrivere un programma C che genera 10 sotto processi.
 Ogni figlio attende il segnale SIGUSR1 ed alla ricezione del segnale
 incrementa il proprio contatore.
 Quando il contatore raggiunge il valore 100, il processo termina.
 Il padre ogni 100 msec invia il segnale SIGUSR1 ad uno dei figli scelti a caso.
 Se un figlio termina, individua quale è terminato e uccide tutti gli altri
 per poi terminare a sua volta.

 */

#include <ourhdr.h>
#include <signal.h>
#include <sys/wait.h>

#define NPROC 10
#define MAXCNT 10

int cnt = 0;

void handler(int p) {
	cnt++;
}


void worker(int id) {
	while( cnt < MAXCNT) {
		pause();
		printf("Cavallo %d posizione %d\n", id, cnt);
	}
	exit(id);
}


int main(void) {
	int pid[NPROC];
	int i;

	if (signal(SIGUSR1, handler) < 0)
		err_sys("signal failed");

	for(i = 0; i < NPROC; i++) {
		if ((pid[i] = fork()) < 0) {
			err_sys("Fork %d failed", i);
		}
		if (pid[i] == 0) {
			worker(i);
		}
		else
			;
	}

	int status, term;
	while(TRUE) {
		// scelgo un processo a caso
		int dst = random() % NPROC;
		if (kill( pid[dst], SIGUSR1) < 0)
			err_sys("send signal to %d", dst);

		usleep(100000); 	// aspetta 100 msec
		if ((term = waitpid( 0, &status, WNOHANG)) < 0)
			err_sys("waitpid failed");
		else if (term > 0)
			break;
	}
	printf("Process %d terminated exit value: %d\n", term, WEXITSTATUS(status));
	if (killpg( getpgrp(), SIGTERM) < 0)
		err_sys("killpg failed");
	// printf("BSD PGID (%d),Padre PGID %d,Figlio PGID %d\n",
	//		getpgrp(), getpgid(getpid()), getpgid(pid[0]));
	return 0;
}
