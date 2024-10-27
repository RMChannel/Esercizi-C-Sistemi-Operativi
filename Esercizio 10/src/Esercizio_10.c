/*

============================================================================

Name        : Esercizio_10.c

Author      :

Version     :

Copyright   : Your copyright notice

Description : Hello World in C, Ansi-style

============================================================================

*/

#define MAXLEN 200
#define MYNAME "Roberto"
#include <ourhdr.h>

void padre(int write_pipe, int read_pipe, const char *name) {
	FILE *f1, *f2;
	f1=fopen(name,"r");
	if(!f1) {
		err_sys("Il file è probabilmente trasceso\n");
	}
	f2=fdopen(read_pipe,"r");
	if(!f2) {
		err_sys("Apertura della pipe uccisa\n");
	}
	char line[MAXLEN];
	char buf[MAXLEN];
	while(fgets(line,MAXLEN,f1)!=NULL) {
		if(write(write_pipe,line,strlen(line))<0) {
			err_sys("La Write non c'è l'ha fatta\n");
		}
		if(fgets(buf,MAXLEN,f2)==NULL) {
			err_sys("La lettura della pipe è stata troppo potente\n");
		}
		printf("Messaggio ricevuto: %s\n",buf);
	}
	close(write_pipe); //Invio di EOF
	close(read_pipe);
	exit(0);
}

void figlio(int read_pipe, int write_pipe) {
	FILE *f;
	if((f=fdopen(read_pipe,"r"))==NULL) {
		err_sys("Errore apertura pipe in lettura\n");

	}
	char buf[MAXLEN];
	while(fgets(buf,MAXLEN,f)!=NULL) {
		buf[strcspn(buf,"\n")]=0;
		char msg[MAXLEN];
		if(strcmp(buf,MYNAME)==0) {
			snprintf(msg,MAXLEN,"Nome trovato: %s\n",buf);
		}
		else snprintf(msg,MAXLEN,"Nome non trovato: %s\n",buf);
		if(write(write_pipe,msg,strlen(msg))<0) err_sys("Il messaggio dal figlio al padre è finito nella 4°dimensione (probabilmente)\n");
	}
	close(write_pipe);
	close(read_pipe);
	exit(0);
}

int main(void) {
	int fd_a[2]; //Pipe Padre-Figlio
	int fd_b[2]; //Pipe Figlio-Padre
	if(pipe(fd_a)<0) err_sys("Pipe Padre-Figilio non è andato\n");
	if(pipe(fd_b)<0) err_sys("Pipe Figlio-Padre non è andato\n");
	pid_t pid=fork();
	if(pid<0) err_sys("Creazione figlio andato a fanculo\n");
	else if(pid==0) {
		close(fd_a[1]); //Chiudo la scrittura della pipe da Padre-Figlio
		close(fd_b[0]); //Chiudo la lettura della pipe da Figlio-Padre
		figlio(fd_a[0],fd_b[1]);
	}

	else {
		close(fd_a[0]);
		close(fd_b[1]);
		padre(fd_a[1],fd_b[0],"testo.txt");
		wait(NULL);
		printf("Figlio terminato\n");

	}
	return 0;
}
