/*
 ============================================================================
 Name        : Es_Memoria.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>
#include <math.h>

void printMatrice(int **A, int n) {
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			printf("%d ",A[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	long memory_size = atol(argv[1]);
	long num_operations = atol(argv[2]);
	int n = sqrt((memory_size*1024L*1024)/12);
	int **A, **B, **C;
	//int A[][], B[][], C[][];
	//ALlocazione matrici
	if((A = calloc(n,sizeof(int *)))==NULL) {
		err_sys("Non posso allocare la matrice A");
	}
	if((B = calloc(n,sizeof(int *)))==NULL) {
		err_sys("Non posso allocare la matrice B");
	}
	if((C = calloc(n,sizeof(int *)))==NULL) {
		err_sys("Non posso allocare la matrice C");
	}
	for(int i=0;i<n;i++) {
		if((A[i]=calloc(n,sizeof(int)))==NULL) {
			err_sys("Allocazione riga %d matrice A non andata a buon fine",i);
		}
		if((B[i]=calloc(n,sizeof(int)))==NULL) {
			err_sys("Allocazione riga %d matrice B non andata a buon fine",i);
				}
		if((C[i]=calloc(n,sizeof(int)))==NULL) {
			err_sys("Allocazione riga %d matrice C non andata a buon fine",i);
		}
	}
	//Ora inizializzazione matrici
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			A[i][j] = (random()%20)-10;
			B[i][j] = (random()%20)-10;
			C[i][j] = (random()%20)-10;
		}
	}
	//printMatrice(A,n);
	//A questo punto inizia il calcolo delle operazioni
	startCounting();
	for(int i=0;i<num_operations;i++) {
		C[random()%n][random()%n] += A[random()%n][random()%n] * B[random()%n][random()%n];
	}
	stopCounting();
	double time=getRealTime();
	printf("%.1f ops/sec\nTempo: %f\nNumero Operazioni: %ld\nN: %d\n",num_operations/time,time,num_operations,n);
	printResourceUsage();
}
