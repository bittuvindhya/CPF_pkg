#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "cpfapi.h"
char* id_validation(char* str){
	int buffer =0;
	int last_uid = 0;
	char *buffer1,*buff;
	char buffer2[100];
	buffer1=(char*)malloc(100*sizeof(char));
	memset(buffer1,0,sizeof(buffer1));
	buffer = atoi(str);
	/*if(buffer > 6000){
		buffer=buffer-5000;
		printf("\nexisting user ,your uid is %d\n",buffer);
		strcpy(buffer1,"existing user ,your uid is ");
		getDecStr(buffer2,4,buffer);
		strcat(buffer1,buffer2);
		return buffer1;
	}*/
	if(buffer >= 1001 && buffer <3000){
		strcpy(buffer1,"your uid is ");
		getDecStr(buffer2,4,buffer);
		strcat(buffer1,buffer2);
		printf("\n ur--->%s",buffer1);
		return buffer1;
	}
	else if(buffer >= 3001 && buffer < 6000){
		printf("\nyour Sid is %d\n",buffer);
		strcpy(buffer1,"Your SID is ");
		getDecStr(buffer2,4,buffer);
		strcat(buffer1,buffer2);
		printf("\n ur--->%s",buffer1);
		return buffer1;
	}
	else if(buffer >= 7000 && buffer < 9000){
                printf("\nyour Session id is %d\n",buffer);
                strcpy(buffer1,"Your Session_ID is ");
                getDecStr(buffer2,4,buffer);
                strcat(buffer1,buffer2);
		buff=svc_field(str);
		printf("filed %s \n",buff);
		strcat(buffer1,"\nEnter your field:");
		strcat(buffer1,buff);
		printf("SESSION Id and filed %s \n",buffer1);
                return buffer1;
        }

}
