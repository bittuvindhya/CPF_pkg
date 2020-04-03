#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char* getfield(){
	char *str=(char*)malloc(15*sizeof(char));
	memset(str,0,sizeof(str));
	strcpy(str,"ifconfig");
	return str;
}
