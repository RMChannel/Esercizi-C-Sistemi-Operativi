/*
Scrivere un programma che prende 3 parametri sulla linea di comando: un pattern (stringa da ricercare), una path di
un file esistente ed un intero n. Il programma dovrà creare n processi figli ognuno dei quali dovrà ricercare il pattern
in una sottosezione (diversa) del file path di dimensione pari a 1/n della taglia totale del file. Il processo padre dovrà
attendere la terminazione di tutti i figli e restituire il numero totale di occorrenze del pattern all’interno dell’intero
file.s
 */

#include <ourhdr.h>

int main(int argc, char *argv[]) {
	int file=open(argv[2],O_RDONLY);
	if(file<0) err_sys("Il file non esiste");

}
