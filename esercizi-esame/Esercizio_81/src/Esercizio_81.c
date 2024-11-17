/*
 Scrivere un programma C che scrive in un file 100.000 interi scelti a caso. Successivamente crea 4 figli Ogni figlio
 processerà l’intero file e, tramite una pipe, indicherà al padre la posizione nel file di ogni intero multiplo rispettiva
mente di 991, 1117, 2221, 3323. Il padre una volta terminati tutti i figli stamperà tutti i risultati ricevuti. Si suggerisce
 di utilizzare la pipe2() con il flag O_NONBLOCK
 */

#include <ourhdr.h>
#include <errno.h>
#define NNUMBERS 100000

void fFiglio(int writePipe, int n) {
	int file=open("numbers.txt",O_RDONLY);
	if(file<0) err_sys("Il file a quanto pare non pensa, poiché non esiste");
	int m;
	for(int i=0;i<NNUMBERS;i++) {
		read(file,&m,sizeof(int));
		off_t position=lseek(file,0,SEEK_CUR);
		if((m%n)==0) write(writePipe,&position,sizeof(off_t));
	}
	close(file);
}

int main(void) {
	int file=open("numbers.txt",O_CREAT | O_WRONLY,0644);
	if(file<0) err_sys("Il file ha deciso di non voler ne esistere ne generarsi, quindi fanculo la vita");
	srand(time(NULL));
	for(int i=0, n;i<NNUMBERS;i++) {
		n=rand();
		write(file,&n,sizeof(int));
	}
	close(file);
	int fd[4][2];
	int numbers[4]={991,1117,2221,3323};
	for(int i=0;i<4;i++) {
		if(pipe2(fd[i],O_NONBLOCK)<0) err_sys("La pipe non esiste");
		pid_t figlio=fork();
		if(figlio<0) err_sys("Figlio %d non ha voluto nascere, fanculo la vita");
		else if(figlio==0) {
			close(fd[i][0]);
			fFiglio(fd[i][1],numbers[i]);
			close(fd[i][1]);
			exit(0);
		}
		else {
			close(fd[i][1]);
		}
	}
	int terminated[4]={1,1,1,1};
	int check=1;
	long int n;
	long int p1[NNUMBERS]={0};
	long int p2[NNUMBERS]={0};
	long int p3[NNUMBERS]={0};
	long int p4[NNUMBERS]={0};
	int id[4]={0};
	long int* p[4]={p1,p2,p3,p4};
	while(check) {
		check=0;
		for(int i=0;i<4;i++) {
			if(terminated[i]) {
				check=1;
				ssize_t control=read(fd[i][0],&n,sizeof(long int));
				if(control==0) {
					terminated[i]=0;
				}
				else if(control>0) {
					p[i][id[i]]=n;
					id[i]++;
				}
				else if (control == -1 && (errno == EWOULDBLOCK || errno == EAGAIN)){
				;//ignoro l'errore
				}
				else{
					err_sys("errore in lettura da pipe %d", i);
				}
			}
		}
	}
	char stampa[]="°figlio:\n";
	for(int i=0;i<4;i++) {
		char result[20];
		close(fd[i][0]);
		sprintf(result,"%d %s",i+1,stampa);
		write(1,result,strlen(result));
		for(int j=0;j<NNUMBERS && p[i][j]!=0;j++) {
			sprintf(result,"%ld\n",p[i][j]);
			write(1,result,strlen(result));
		}
	}
}
