#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char* getsessiontype(){
	char *str=(char*)malloc(15*sizeof(char));
	memset(str,0,sizeof(str));
	strcpy(str,"interactive");
	return str;
}

