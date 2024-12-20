/*
 Scrivere un programma C che sulla riga di comando legge la path di una directory esistente. Il programma creerà
 un processo che eseguirà il comando di sistema ls nella directory specificata. Il processo padre, catturando l’output
 prodotto dal comando, aprirà tutti i file presenti nella directory contando il numero di occorrenze del carattere ‘\n’
 presenti in ciascun file. Al termine il totale verrà stampato sullo standard output
 */

#include <ourhdr.h>

int main(int argc, char *argv[]) {
	int fd[2];
	//Mi creo la pipe
	if(pipe(fd)<0) err_sys("Pipe andata a puttane\n");
	pid_t figlio=fork(); //Creo il figlio
	//Entro nel figlio
	if(figlio==0) {
		close(fd[0]); //Chiudo la pipe in lettura
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",argv[1],NULL);
		exit(0);
	}
	//Errore figlio
	else if(figlio<0) {
		err_sys("Figlio andato a puttane\n");
	}
	//Padre
	else {
		close(fd[1]); //Chiudo la pipe in scrittura
		char buffer[500];
		if(read(fd[0],buffer,sizeof(buffer))<0) err_sys("Lettura da pipe non andata a buon fine\n");
		int count=0, j=0;
		char *result=calloc(sizeof(char),100);
		char *resultOriginal=result;
		char path[100];
		strcpy(path,argv[1]);
		for(int i=0;i<strlen(buffer);i++) {
			if(buffer[i]!='\n') {
				result[j]=buffer[i];
				j++;
			}
			else {
				int file;
				strcat(path,resultOriginal);
				if((file=open(path,O_RDONLY))<0) err_sys("Errore apertura file\n");
				else{
					while(read(file,resultOriginal,sizeof(resultOriginal))>0) {
						for(j=0;j<strlen(result);j++) if(result[j]=='\n') count++;
					}
				}
				for(j=0;j<100;j++) result[j]='\0';
				j=0;
				strcpy(path,argv[1]);
			}
		}
		sprintf(resultOriginal,"%d",count);
		write(1,resultOriginal,sizeof(resultOriginal));
	}
}
