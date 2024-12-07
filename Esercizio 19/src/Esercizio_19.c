/*
 ============================================================================
 Name        : Esercizio_19.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>
#include <dirent.h>
#include <limits.h>
int maxLevel=0;
char maxpath[PATH_MAX];

void visitaDirectory(char *dirpath, int livello) {
	if(livello>maxLevel) {
		maxLevel=livello;
		strcpy(maxpath,dirpath);
	}
	DIR *dir;
	char newpath[PATH_MAX];

	if((dir=opendir(dirpath))==NULL) {
		err_sys("Directory not found %s",dirpath);
	}
	struct dirent *directory;
	while((directory=readdir(dir))!=NULL) {
		if(strcmp(directory->d_name,".")==0 || strcmp(directory->d_name,"..")==0) {
			continue;
		}
		if(directory->d_type==DT_DIR) {
			snprintf(newpath,PATH_MAX,"%s/%s",dirpath,directory->d_name);
			visitaDirectory(newpath,++livello);
		}
		if(directory->d_type==DT_DIR) printf("%s ",newpath);
		printf("Nome entry: %s, tipo entry: %d\n",directory->d_name,directory->d_type);
	}
	closedir(dir);
}

int main(int argc, char *argv[]) {
	if(argc!=2) err_sys("Uso corretto: ./program <directory>");
	visitaDirectory(argv[1],0);
	printf("%s %d",maxpath,maxLevel);
}
