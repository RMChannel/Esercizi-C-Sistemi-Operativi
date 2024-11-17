/*
 Scrivere un programma C che prende sulla linea di comando un numero arbitrario di path (stringhe). Per ogni path,
 il main dovrà creare un sotto processo che esegue il comando /bin/ls sulla path indicata. Il processo padre dovrà
 attendere la terminazione di tutti i figli prima di stampare il numero totale dei processi eseguiti con successo (exit
 code = 0) ed uscire. A scelta del candidato: il processo padre potrà contare anche il numero totale di file (parole)
 restituiti da ciascun figlio su stdout attraverso una pipe dedicata.
 */

#include <ourhdr.h>

void fFiglio(char *path) {
    execlp("ls", "ls", path, NULL);
    // Se execlp fallisce
    perror("execlp");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path1> <path2> ...\n", argv[0]);
        exit(1);
    }

    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }

    int count_success = 0;

    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {  // Processo figlio
            close(fd[0]); // Chiudi il lato di lettura del pipe
            dup2(fd[1], STDOUT_FILENO); // Redireziona stdout al pipe
            close(fd[1]); // Chiudi il lato di scrittura duplicato
            fFiglio(argv[i]); // Esegui ls
        }
    }

    close(fd[1]); // Chiudi il lato di scrittura nel processo padre

    // Attendere la terminazione di tutti i figli
    for (int i = 1; i < argc; i++) {
        int status;
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            count_success++;
        }
    }

    // Leggere dal pipe
    char buffer[100];
    int countWord = 0;
    ssize_t bytesRead;
    while ((bytesRead = read(fd[0], buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < bytesRead; i++) {
            if (buffer[i] == '\n' || buffer[i] == ' ') {
                countWord++;
            }
        }
    }
    close(fd[0]); // Chiudi il lato di lettura

    printf("Numero di processi con successo: %d\n", count_success);
    printf("Numero totale di parole: %d\n", countWord);

    return 0;
}

