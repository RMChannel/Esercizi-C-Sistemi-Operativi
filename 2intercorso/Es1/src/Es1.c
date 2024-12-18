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
#include <dirent.h>

int main(int argc, char *argv[]) {
	if(argc!=2) err_sys("Uso corretto: ./es1 <path>");
	DIR *dir;
	struct dirent *dt;
	dir=opendir(argv[1]);
	if(dir==NULL)err_sys("Errore lettura path");
	while((dt=readdir(dir))!=NULL) {
		if(dt->d_type!=DT_DIR) {
			struct stat buffer;
			char path[300]="";
			snprintf(path,300,"%s/%s",argv[1],dt->d_name);
			if(stat(path,&buffer)<0) {
				err_sys("stat andata a puttane");
			}
			if(buffer.st_size==0) write(1,path,sizeof(path));
		}
	}
}