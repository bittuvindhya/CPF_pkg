#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char* getuid(){
	char *str=(char*)malloc(15*sizeof(char));
	memset(str,0,sizeof(str));
	strcpy(str,"1001");
	return str;
}

