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

int main(void) {
		srand(time(NULL));
		int fd=open("test.txt",O_CREAT | O_RDWR,0644);
		startCounting();
		int m, n=10000, l, count=0;
		for(int i=0;i<n;i++) {
			m=rand()%1001;
			char number[100]="";
			int temp=m;
			while(temp>0){
				temp/=10;
				count++;
			}
			if((i+1)%6==0) number[count]='\n';
			else number[count]=' ';
			while(m>0) {
				l=m%10;
				m/=10;
				number[count-1]=l+'0';
				count--;
			}
			write(fd,number,strlen(number));
			printf("%s",number);
		}
		close(fd);
		stopCounting();
		printResourceUsage();
		return 0;
	}
