#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	fcntl(STDIN_FILENO,F_SETFL, O_NONBLOCK);
	char test;
	//test=(char*)malloc(10*sizeof(char));
	while(1){
	//printf("prout\n");
	//usleep(100000);
	test=getchar();
	printf("%c\n",test);
	//if(!strcmp(test,"EAGAIN")){
	//	printf("lol_\n");
	//}
	}
	return 0;}
