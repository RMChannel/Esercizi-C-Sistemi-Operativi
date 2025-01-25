#include <ourhdr.h>
#include <dirent.h>
#include <limits.h>
/*1. SCRIVERE UN PROGRAMMA CHE PRENDE DALLA LINEA DI COMANDO UNA DIRECTORY E STAMPA IN OUTPUT TUTTE LE DIRENTRY CHE TROVA IN QUELLA DIRECTORY
 *2. SCRIVERE UN PROGRAMMA CHE PRENDE DALLA LINEA DI COMANDO UNA DIRECTORY E VISITA IN MANIERA RICORSIVA TUTTO IL SOTTOALBERO CON RADICE LA DIRECTORY PASSATA
 *3. SCRIVERE UN PROGRAMMA CHE PRENDE DALLA LINEA DI COMANDO UNA DIRECTORY E RESTITUISCE IL PERCORSO PIU LUNGO PARTENDO DAL PATH PASSATO COME ARGOMENTO
 */
int maxdepth = 0;

void visitaDir(char *path, int livello);

int main(int argc, char *argv[]) {
	if (argc != 2)
		err_sys("passa una directory");

	visitaDir(argv[1], 0);

	printf("Il livello massimo di profondita' e' %d\n", maxdepth);

	return 0;
}

void visitaDir(char *path, int livello) {
	DIR *dir;
	char currentpath[PATH_MAX];

	if ((dir = opendir(path)) == NULL) //Apertura cartella data una path
		err_sys("apertura directory %s fallita", path);
	struct dirent *dt;

	while ((dt = readdir(dir)) != NULL) { //Legge la cartella in una struct DIR e legge file per file ad ogni iterazione
		if (strcmp(dt->d_name, ".") == 0 || strcmp(dt->d_name, "..") == 0) //Esclude il . e il .. che compaiono ogni volta che si apre una directory
			continue;

		if (dt->d_type == DT_DIR) { //Controlla se il file dato è una cartella
			snprintf(currentpath, PATH_MAX, "%s/%s", path, dt->d_name);
			visitaDir(currentpath, ++livello); //Chiamata ricorsiva
		}

		if (dt->d_type == DT_DIR)
			printf("%s\n", currentpath);
		else
			printf("%s\n", dt->d_name);
	}
	closedir(dir);

	if (livello > maxdepth)
		maxdepth = livello;
}
