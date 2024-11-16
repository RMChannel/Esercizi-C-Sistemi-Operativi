/*
 Scrivere un programma C che crea 4 processi, denominati A, B, C, D. A è il main e crea B, che a sua volta crea C che
 provvede alla creazione di D. I 4 processi devono comunicare in maniera circolare attraverso l’uso della system call
 pipe() di Unix e cioè A invia una stringa a B, B aggiunge il proprio PID e invia la stringa a C che a sua volta aggiunge il
 proprio PID e invia il messaggio completo a D. Al termine D, aggiunge il proprio PID ed invia il messaggio di nuovo ad
 A. A sceglie i 4 messaggi da inviare (una stringa costituita da un numero casuale di 8 cifre) e dopo aver ricevuto le 4
 risposte, invia un messaggio di terminazione (-1), ed aspetta la terminazione di B (tutti i processi devono terminare)
 */

#include <ourhdr.h>
#define DIM_BUF 100

void figlio(int toClose1, int readPipe, int toClose2, int writePipe) {
	close(toClose1);
	close(toClose2);
	char message[DIM_BUF]="";
	char toSend[DIM_BUF]="";
	read(readPipe,message,DIM_BUF);
	sprintf(toSend,"%s %d",message,getpid());
	write(writePipe,toSend,strlen(toSend));
	close(readPipe);
	close(writePipe);
}

int main(void) {
	int fdAB[2];
	int fdDA[2];
	if(pipe(fdAB)<0) err_sys("Creazione pipe tra A e B non andata a buon fine");
	if(pipe(fdDA)<0) err_sys("Creazione pipe tra D e A non andata a buon fine");
	pid_t B=fork();
	if(B<0) err_sys("Creazione di B non andata a buon fine");
	else if(B==0) {
		int fdBC[2];
		if(pipe(fdBC)<0) err_sys("Creazione pipe tra B e C non andata a buon fine");
		pid_t C=fork();
		if(C<0) err_sys("Creazione di C non andata a buon fine");
		else if(C==0) {
			int fdCD[2];
			if(pipe(fdCD)<0) err_sys("Creazione pipe tra C e D non andata a buon fine");
			pid_t D=fork();
			if(D<0) err_sys("Creazione di D non andata a buon fine");
			else if(D==0) {
				figlio(fdCD[1],fdCD[0],fdDA[0],fdDA[1]);
				exit(-1);
			}
			else {//CI TROVIAMO NEL PROCESSO C
				figlio(fdBC[1],fdBC[0],fdCD[0],fdCD[1]);
				exit(-1);
			}
		}
		else {//CI TROVIAMO NEL PROCESSO B
			figlio(fdAB[1],fdAB[0],fdBC[0],fdBC[1]);
			exit(-1);
		}
	}
	//CI TROVIAMO IN A
	close(fdAB[0]);
	close(fdDA[1]);
	char stringa[5]="CIAO";
	write(fdAB[1],stringa,strlen(stringa));
	char message[DIM_BUF]="";
	read(fdDA[0],message,DIM_BUF);
	close(fdAB[1]);
	close(fdDA[0]);
	wait();
	write(1,message,strlen(message));
}
