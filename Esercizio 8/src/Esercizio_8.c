/*
 ============================================================================
 Name        : Esercizio_8.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ourhdr.h>

int main(void) {
	char *words="Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent eget metus velit. Proin risus augue, malesuada id semper at, efficitur quis justo. Cras ut augue ornare, facilisis risus a, facilisis arcu. Nulla et felis a erat placerat rutrum sit amet dapibus neque. Praesent volutpat posuere lorem, accumsan hendrerit ex porttitor id. Vestibulum eleifend eros at lorem lobortis, ac cursus mauris interdum. Maecenas tempus nibh nec hendrerit fermentum. Donec tempor lorem vitae luctus ultrices. Praesent fringilla tempor turpis, id elementum risus rutrum non. Suspendisse condimentum egestas sagittis. Duis ac posuere lorem. Fusce bibendum finibus consequat. Sed tellus leo, maximus at arcu a, tempor scelerisque quam. Pellentesque faucibus varius mauris, sit amet rutrum arcu.\nPraesent quis ante tincidunt, pulvinar nibh eget, gravida eros. Sed in arcu condimentum, dignissim lorem in, sollicitudin augue. Nunc ipsum eros, lobortis quis velit ut, elementum faucibus libero. Sed quis sem id dolor aliquam pulvinar. Nulla ultricies sit amet diam id tristique. Praesent in consequat massa. Sed congue imperdiet ante sed malesuada. Sed dictum varius ipsum, non interdum quam pretium sed. Nullam eu nibh elementum, sodales ante a, mollis lorem. Vestibulum sit amet tempor metus. Quisque sit amet odio consectetur, lobortis turpis nec, convallis risus. Fusce volutpat odio sodales, congue nisi at, blandit ante. Donec tristique rutrum sem ut semper.\nMorbi dictum convallis sapien, feugiat aliquet dui fermentum in. Duis bibendum auctor justo dignissim tempor. Cras magna dolor, viverra vel tempor eu, efficitur vitae massa. Vivamus non aliquet arcu, non scelerisque dolor. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum congue cursus ligula in consectetur. Mauris semper odio orci, eget laoreet justo congue rutrum. Duis non turpis vitae sapien suscipit sodales. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Proin ut sagittis lorem. Maecenas ac purus ex. Mauris pretium, metus vitae posuere varius, velit felis venenatis nisl, posuere molestie risus ipsum sed ipsum. Nam laoreet sed diam sit amet volutpat. Sed risus eros, viverra non rutrum non, sodales quis mauris.\nVestibulum ;bibendum, nisl sed interdum suscipit, diam leo pulvinar nulla, vitae ultricies velit metus sit amet magna. Morbi quis dui eu tortor rhoncus porttitor. Donec ullamcorper purus at neque mollis dapibus. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Morbi malesuada enim eros, vitae placerat leo posuere tincidunt. Pellentesque ac sem a tortor gravida consectetur at ac diam. Etiam gravida, dolor eu eleifend condimentum, ipsum sapien bibendum.";
	pid_t figlio;
	figlio=fork();
	int status;
	if(figlio==0) {
		int fd=open("output.txt",O_CREAT | O_RDWR,0644);
		write(fd,words,strlen(words));
	}
	wait(&status);
	int fd=open("output.txt", O_RDONLY);
	char s[5000];
	int n=read(fd,s,sizeof(s));
	s[n]='\0';
	printf("%s",s);
	return EXIT_SUCCESS;
}
