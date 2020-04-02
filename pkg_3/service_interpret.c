#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include "validation1.h"

char *service(char *cBuffer){
	char *buffer;
	cBuffer[strlen(cBuffer)] = '\0';

	if(strlen(cBuffer) != NULL){
		buffer = NULL;
	
		if(strncmp(cBuffer,"ifconfig", 8) == 0) {
			printf("INFO: Generating ifconfig output\n"); 
			buffer = ifconfig();
		}
		else {
			printf("ERROR: ifconfig expected, but not received in input\n"); 
			return NULL;
		}

		return buffer;
	}
	else{
		printf("\nEnter valid field\n");
		return NULL;
	}
}


