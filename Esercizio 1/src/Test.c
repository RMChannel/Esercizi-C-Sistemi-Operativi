/*
 ============================================================================
 Name        : Test.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <ourhdr.h>

int toInt(char* n) {
	int result=0;
	while(*n) {
		result=(*n)-'0'+(result*10);
		n++;
	}
	return result;
}

int main(int argc, char* argv[]) {
		srand(time(NULL));
		int n;
		if(argc==1) n=10000;
		else n=toInt(argv[1]);
		int fd;
		if((fd=open("test.txt",O_CREAT | O_RDWR,0644))<0) {
			write(2,"File non aperto/generato correttamente\n",sizeof(char)*40);
			return -1;
		}
		startCounting();
		int m, l, count=0, temp;
		for(int i=0;i<n;i++) {
			m=rand()%1001;
			char number[20]="";
			temp=m;
			while(temp>0){
				temp/=10;
				count++;
			}
			temp=count+1;
			if((i+1)%6==0) number[count]='\n';
			else number[count]=' ';
			while(m>0) {
				l=m%10;
				m/=10;
				number[count-1]=l+'0';
				count--;
			}
			write(fd,number,temp);
			write(1,number,temp);
		}
		close(fd);
		stopCounting();
		printResourceUsage();
		return 0;
	}
