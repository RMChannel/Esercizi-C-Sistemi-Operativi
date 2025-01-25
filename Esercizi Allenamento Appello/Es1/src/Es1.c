/*
 ============================================================================
 Name        : Es1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

int main(int argc, char *argv[]) {
	srand(time(NULL));
	if(argc!=2) perror("Uso corretto: ./main <n>");
	int n=atoi(argv[1]);
	int fd=open("test.txt",O_CREAT | O_RDWR,0644);
	if(fd<0) perror("File non aperto correttamente");
	int *randomN=malloc(sizeof(int));
	for(int i=0;i<n;i++) {
		*(randomN)=rand()%1001;
		//printf("%d\n",*randomN);
		if(write(fd,randomN,sizeof(int))<0) perror("Scrittura non adata a buon fine");
	}
	lseek(fd,0,SEEK_SET);
	for(int i=0;i<n;i++) {
		if(read(fd,randomN,sizeof(int))<0) perror("Lettura non andata a buon fine");
		printf("%d\n",*randomN);
	}
	free(randomN);
	close(fd);
	return 0;
}
