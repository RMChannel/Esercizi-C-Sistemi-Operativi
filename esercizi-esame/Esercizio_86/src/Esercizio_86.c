/*
Scrivere un programma C che attraverso le principali System Call di Unix crei 10 file in una directory con il nome
“pluto-x” dove 0 < x < 11 con permessi 640. Successivamente scrivere una funzione che provvede a rinominare tutti i
file con x pari in “paperino-y” dove y è x-1 e a cancellare tutti i file con x % 3 == 0
 */

#include <ourhdr.h>

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
