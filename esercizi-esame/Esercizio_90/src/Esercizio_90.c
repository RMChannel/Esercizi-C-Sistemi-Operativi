/*
Scrivere un programma C che legge dalla linea di comando una lista di directory. Per ognuna di queste un processo
figlio eseguirà il comando ls -l dir. Il processo padre salverà in un file dir.txt solo i nomi dei file prodotti nell’output
del comando eseguito
 */

#include <ourhdr.h>
#define DIM_BUFFER 1000

void estraiNomeFile(char *riga, char *nomeFile) {
    // Trova l'ultimo spazio nella riga, che separa l'output dal nome del file
    char *ultimoSpazio = strrchr(riga, ' ');
    if (ultimoSpazio != NULL) {
        // Copia il nome del file ignorando spazi iniziali
        strcpy(nomeFile, ultimoSpazio + 1);
        // Rimuovi il carattere di newline alla fine (se presente)
        size_t len = strlen(nomeFile);
        if (len > 0 && nomeFile[len - 1] == '\n') {
            nomeFile[len - 1] = '\0';
        }
    } else {
        // Se non trova l'ultimo spazio, ritorna la riga originale
        strcpy(nomeFile, riga);
    }
}

void fFiglio(char *path, int writePipe) {
	dup2(writePipe,STDOUT_FILENO);
	execlp("ls","ls","-l",path,NULL);
}

int main(int argc, char *argv[]) {
	int fd[argc-1][2];
	for(int i=1;i<argc;i++) {
		if(pipe(fd[i-1])<0) err_sys("Pipe ha deciso che c'è il calcio di rigore al 90'");
		pid_t figlio=fork();
		if(figlio<0) err_sys("Figlio %d andato a puttane",i+1);
		else if(figlio==0) {
			close(fd[i-1][0]);
			fFiglio(argv[i],fd[i-1][1]);
			exit(0);
		}
		else {
			close(fd[i-1][1]);
		}
	}

	wait();
	int file=open("dir.txt",O_CREAT | O_WRONLY, 0644);
	for(int i=0;i<argc;i++) {
		 char result[DIM_BUFFER];
		 char nomeFile[DIM_BUFFER];
		 int bytesRead;
		 // Inizializza il buffer per la lettura
		 while ((bytesRead = read(fd[i][0], result, DIM_BUFFER - 1)) > 0) {
			 result[bytesRead] = '\0'; // Aggiungi terminatore di stringa
		     // Suddividi l'output in righe e fai il parsing
		     char *riga = strtok(result, "\n");
		     while (riga != NULL) {
		     if (strncmp(riga, "total", 5) == 0) {
		    	 riga = strtok(NULL, "\n");
		         continue;
		     }
		     estraiNomeFile(riga, nomeFile);
		     write(file,nomeFile,strlen(nomeFile));
		     write(file,"\n",1);
		     riga = strtok(NULL, "\n");
		     }
		 }
		 close(fd[i][0]);
	}
	return 0;
}
