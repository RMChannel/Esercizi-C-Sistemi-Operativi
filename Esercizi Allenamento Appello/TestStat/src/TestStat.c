/*
 ============================================================================
 Name        : TestStat.c
 Author      : Pipp8
 Version     :
 Copyright   : Corso di Sistemi Operativi a.a. 2024-2025
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/*
 * Scrivere un programma C che legge dalla riga di comando una lista di filename
 * e per ognuno di questi stampa tutti i metadati disponibili.
 * [+] prende in input una directory e stampa tutti i metadati di tutti i file
 *
 * Scrivere un programma che crea un file scrive 1 intero all'inizio del file
 * sposta il puntatore di 10.000.000 di byte in avanti e scrive un altro intero
 * */

#define  __USE_GNU 1

#include <ourhdr.h>
#include <sys/sysmacros.h>


/* Macros for converting between `struct timeval' and `struct timespec'.  */
# define TIMEVAL_TO_TIMESPEC(tv, ts) {                              \
	(ts)->tv_sec = (tv)->tv_sec;                                    \
	(ts)->tv_nsec = (tv)->tv_usec * 1000;                           \
}
# define TIMESPEC_TO_TIMEVAL(tv, ts) {                                   \
	(tv)->tv_sec = (ts)->tv_sec;                                    \
	(tv)->tv_usec = (ts)->tv_nsec / 1000;                           \
}




void printStat(char *filename){
	struct stat buffer;
	if(stat(filename,&buffer)<0)
		err_sys("cannot stat %s", filename);

	printf("Nome: %s\nMode: 0%o #link: %ld Proprietario: %d Gruppo: %d\n",
						filename, buffer.st_mode, buffer.st_nlink, buffer.st_uid, buffer.st_gid);
	printf("Size: %ld #Blocchi: %ld BlockSize: %ld\n",
					buffer.st_size, buffer.st_blocks, buffer.st_blksize);
	printf("dev: 0x%lx Major: %d Minor: %d\n",
			buffer.st_dev, major(buffer.st_dev),  minor(buffer.st_dev));
	printf("Data creazione: %s", ctime(&(buffer.st_ctim.tv_sec)));
	printf("Data dataUltimaModifica:  %s", ctime(&(buffer.st_mtim.tv_sec)));
	printf("Data accesso:   %s\n", ctime(&(buffer.st_atim.tv_sec)));
	return;
}



int main(int argc, char *argv[]) {
	if(argc == 1){
		printf("Hai dimenticato di inserire gli argomenti");
		exit(-1);
	}

	for(int i=1; i<argc; i++){
		printStat(argv[i]);

	}


	/*
	 * seconda parte della traccia
	 *
	 * sistema per evidenziare il metodo di allocazione
	 * utilizzato dal file system sottostante
	 * nel caso di file con pezzi non utilizzati.
	 * N.B. attenzione alla differenza nel caso di FAT vs EXT4
	 */
 	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if(fd < 0)
		err_sys("Open");
	int x = 1;
	if(write(fd, &x, sizeof(int)) < 0)
		err_sys("Write 1");
	if(lseek(fd, 10000000l, SEEK_CUR) < 0)
		err_sys("Seek");
	x = 0x04030201;
	if(write(fd, &x, sizeof(int)) < 0)
		err_sys("Write 2");
	close(fd);

	if((fd = open(argv[1], O_RDONLY)) < 0)
		err_sys("Open read only");
	int rd;
	char temp;
	while((rd = read(fd, &temp, sizeof(char))) > 0)
		printf("%o ", temp);
	if(rd < 0)
		err_sys("read");
	else
		printf("EOF\n");
	close(fd);

	printStat(argv[1]);

	return 0;
}

