/*
 Scrivere un programma che prende 3 parametri sulla linea di comando: un pattern (stringa da ricercare), una path di
 un file esistente ed un intero n. Il programma dovrà creare n processi figli ognuno dei quali dovrà ricercare il pattern
 in una sottosezione (diversa) del file path di dimensione pari a 1/n della taglia totale del file. Il processo padre dovrà
 attendere la terminazione di tutti i figli e restituire il numero totale di occorrenze del pattern all’interno dell’intero
 file.s
 */

#include <ourhdr.h>
#define BUFFER_DIM 1000

int myAtoi(char *string) {
	int n=0, temp;
	while(*string) {
		temp=(*string)-'0';
		n=(n*10)+temp;
		string++;
	}
	return n;
}

void fFiglio(int file, int writePipe, int i, int n, off_t mid, char *word) {
	char buffer[BUFFER_DIM]="";
	if(read(file,buffer,BUFFER_DIM)<0) err_sys("Lettura dal file non andata a buon fine %d",i);
	char *pos=buffer;
	int count=0;
	if(i==(n-1)) {
		while ((pos = strstr(pos, word)) != NULL) {
			count++;
			pos += strlen(word);
		}
	}
	else {
		while ((pos = strstr(pos, word)) != NULL && (pos-buffer)<mid) {
			count++;
			pos += strlen(word);
		}
	}
	write(writePipe,&count,sizeof(int));
}

int main(int argc, char *argv[]) {
	if(argc<4) err_sys("Uso corretto: <word> <path> <n process>");
	int file = open(argv[2], O_RDONLY);
	if (file < 0) err_sys("Il file non esiste");
	int n=myAtoi(argv[3]);
	off_t mid = lseek(file, 0, SEEK_END)/n;
	int fd[2];
	if(pipe(fd)<0) err_sys("Pipe andata a puttane");
	for(int i=0;i<n;i++) {
		pid_t figlio=fork();
		if(figlio<0) err_sys("Figlio %d andato a puttane",i+1);
		else if(figlio==0) {
			file=open(argv[2],O_RDONLY);
			for(int j=0;j<i;j++) lseek(file,mid,SEEK_CUR);
			close(fd[0]);
			fFiglio(file,fd[1], i, n, mid,argv[1]);
			exit(0);
		}
	}
	close(fd[1]);
	int respond=0, count=0;
	while(respond<n) {
		for(int i=0;i<n;i++) {
			int result;
			ssize_t control=read(fd[0],&result,sizeof(int));
			if(control>0) {
				respond++;
				count+=result;
			}
		}
	}
	char result[10];
	sprintf(result,"%d",count);
	write(1,result,strlen(result));
	return 0;
}
