/*
Scrivere un programma C in cui il processo padre apre due pipe e crea un processo figlio. Il padre apre un file e legge
 riga per riga il contenuto inviando la riga letta al processo figlio. Questo leggendo dalla pipe elimina tutte le vocali
 dalla linea ricevuta. Al termine rimanda la stringa risultante al padre. Il padre stampa la stringa ricevuta e legge
 la prossima linea del file. Quanto raggiunge l’EOF manda la stringa “fine” ed aspetta la terminazione del figlio. Il
 processo figlio ricevuta la stringa “fine” chiude le pipe e termina restituendo al padre il numero di vocali eliminate
 */

#include <ourhdr.h>
#define DIM_BUF 200

int mystrcmp(char *s1, char *s2) {
	char *rs2=s2;
	while(*s1 && *s2) {
		if((*s1)==(*s2)) {
			s1++;
			s2++;
		}
		else {
			s1--;
			s2=rs2;
		}
	}
	if(!(*s2)) return 1;
	else return 0;
}

int isVocal(char c) {
	switch(c) {
	case('a'):
	case('e'):
	case('i'):
	case('o'):
	case('u'):
	case('A'):
	case('E'):
	case('I'):
	case('O'):
	case('U'):
			return 1;
	default:
			return 0;

	}
}

int removeVocali(char *stringa) {
	int n=0;
	while(*stringa) {
		if(isVocal(*stringa)) {
			(*stringa)=' ';
			n++;
		}
		stringa++;
	}
	return n;
}

void fFiglio(int readPipe, int writePipe) {
	char message[DIM_BUF]="";
	FILE * f=fdopen(readPipe,"r");
	int n=0;
	while(fgets(message,DIM_BUF,f)!=NULL) {
		n+=removeVocali(message);
		write(writePipe,message,strlen(message));
	}
	close(readPipe);
	write(writePipe,&n,sizeof(int));
}

int main(void) {
	int fd1[2],fd2[2];
	if(pipe(fd1)<0) err_sys("La pipe è stronza oggi e non vuole funzionare");
	if(pipe(fd2)<0) err_sys("L'altra si aggiunge");
	pid_t figlio=fork();
	if(figlio<0) err_sys("Il figlio è l'anticristo e ha deciso che oggi non si studia SO");
	else if(figlio==0) {
		close(fd1[1]);
		close(fd2[0]);
		fFiglio(fd1[0],fd2[1]);
		exit(0);
	}
	close(fd1[0]);
	close(fd2[1]);
	int f=open("aa.log",O_RDONLY);
	FILE *file=fdopen(f,"r");
	if(file==NULL) err_sys("The file is in Amazzonia, com cazz ci arriva giustamente");
	char message[DIM_BUF]="";
	while(fgets(message,DIM_BUF,file)!=NULL) {
		write(fd1[1],message,strlen(message));
		read(fd2[0],message,DIM_BUF);
		write(1,message,strlen(message));
		sleep(0.5);
	}
	write(fd1[1],"fine",4);
	close(fd1[1]);
	int n;
	read(fd2[0],message,DIM_BUF);
	ssize_t control=read(fd2[0],&n,sizeof(int));
	if(control<0) err_sys("Read andata a puttane");
	close(fd2[0]);
	sprintf(message,"%d",n);
	write(1,message,strlen(message));
	wait();
}
