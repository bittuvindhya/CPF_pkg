#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char *change(char *cBuffer){
	char *str,*str_name,*str_type,*str_field,*str_status;
	str=(char*)malloc(100*sizeof(char));
	int i=0,j = 0;
	for( i=0;i<4;i++){
		if(i==0){
			str=strtok(cBuffer,",");
			strncpy(str_name,str,strlen(str));
			printf("str_name-- >%s",str_name);
		}
		if(i==1){
			str=strtok(NULL,",");
			strncpy(str_type,str,strlen(str));
			printf("str_name-- >%s",str_type);
		}
		if(i==2){
			str=strtok(NULL,",");
			strncpy(str_field,str,strlen(str));
			printf("str_name-- >%s",str_field);
		}
		if(i==3){
			str=strtok(NULL,",");
			strncpy(str_status,str,strlen(str));
			printf("str_name-- >%s",str_status);
		}
		return str_type;
	}
}
void main(){
	char *str ="name,type,field,status";
	chat *str1;
	str1 = check (str);
	printf("str1--->%s",str1);
}
