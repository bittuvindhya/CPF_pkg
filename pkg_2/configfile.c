#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include"validation1.h"
#define MAX 2048

char *ifconfig(){

	char *buffer;

        buffer=(char *)malloc(MAX *sizeof(char));
	strcpy(buffer,"ifconfig | head -100 > ifconfig.txt");
        system(buffer);
        memset(buffer,0, MAX);
        
	FILE *fp=fopen("ifconfig.txt","r");

	if (fp == NULL) {
		printf("ERROR: unable to open file : (%d)..\n", errno);
		return NULL;
	}

        int b_read = fread(buffer,MAX,1,fp);

	strcat(buffer,"$");
        printf("%s", buffer);

	fclose(fp);
	return buffer;
}

