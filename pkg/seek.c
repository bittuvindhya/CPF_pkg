#include <stdio.h> 
#include <string.h> 
#include<stdlib.h>
#include "cpfapi.h"

int uid_retrive() 
{ 
	char buff[1024],*str,*token;
     	int count=0,last=0,i=0,regid=1000;
     	FILE *fp = fopen("uid_table.csv","r");
	if(fp==NULL){
		printf("\nCan't open the file\n");
	}
     	while(fgets(buff,1024,(FILE*)fp)){
		count++;
	}
     	fclose(fp);
     	last=--count;
     	fp = fopen("uid_table.csv","r");
	if(fp==NULL){
		printf("\nCan't open the file\n");
	}
	count=1;
     	while(fgets(buff,1024,(FILE*)fp)){
		count++;
	     	if(count==last){
			token=strtok(buff,",");
			regid=atoi(token);
		}
	}
	return regid;
}

