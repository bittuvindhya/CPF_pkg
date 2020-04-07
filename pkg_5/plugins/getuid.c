#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char* getuid(){
	char *str=(char*)malloc(15*sizeof(char));
	memset(str,0,sizeof(str));
	strcpy(str,"1006");
	int i =0;
	for(i=0;i<strlen(str);i++)
		printf("str[%d] -->%c",i,str[i]);
	return str;
}

