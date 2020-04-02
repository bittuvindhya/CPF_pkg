#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <regex.h>
#include<ctype.h>
#include<stdbool.h>
#include "validation.h"
#define MAX 2048

int main_validation(char *cBuffer,int uid){
	int len=0,i=0,val_command=0,l=0,count=0,k=0;
	static int reg_user=0;
	char *command = NULL,*buffer = NULL,*cbuffer = NULL,*buff = NULL;
	bool flag1=false;
	command=(char*)malloc(MAX*sizeof(char));
	buffer=(char*)malloc(MAX*sizeof(char));
	len=strlen(cBuffer);
	//printf("\n buffer=%s,uid=%d",cBuffer,uid);
	//printf("\n length of buffer =%d",len);
	if(strncmp(cBuffer,"QUIT",4) == 0)
		return 10;
	if(strncmp(cBuffer,"ifconfig",8)==0)
		val_command = 2 ;
	if(len==1)
	printf("\n Please,Enter command\n");
	else{
		strcpy(buffer,cBuffer);
		command=strtok(buffer,":");
		l=strlen(command);
		if(flag1==false){
			command[l]='\0';
			val_command=command_checking(command);
			if(val_command > 0 ){
				command[l]='\0';
			}
			else{
				printf("\n Please Enter valid command\n");
			}
			if(strncmp(command,"REG_USR",7)==0){
				count=reg_usr_validation(cBuffer);
				if(count==1){
					reg_user++;
				}
				if(reg_user<=1)
					return count;
				else
					printf("\n Your already registered user,cannot register again\n");
			}
	
			else if(strncmp(command,"GET_SVC_LIST",12)==0){
				if(reg_user==1)
					return svc_list_validation(cBuffer,uid);
				else
					printf("\n First you need to register,enter REG_USR command\n");
			}
			else if(strncmp(command,"SUBSCRIBE",9)==0){
				if(reg_user==1)
					return subscribe_validation(cBuffer,uid);

				else
					printf("\n First you need to register,enter REG_USR command\n");

			}
			else if(strncmp(command,"START_SESSION",13)==0){
				if(reg_user==1)
					return start_session_validation(cBuffer,uid);

				else
					printf("\n First you need to register,enter REG_USR command\n");

			}
			else if(strncmp(cBuffer,"ifconfig",8)==0){
                		if(reg_user==1)
                          		return ifconfig(cBuffer);
				else
                        		printf("\n First you need to register,enter REG_USR command\n");

        		}

			else{
				printf("\n Sorry,Please check your command \n");
			}

		}
	}
//free(command);
//free(buffer);
}

int command_checking(char *str){
	bool flag1=false;
	int i=0;
	for(i=0;i<strlen(str);i++){
        	if((isupper(str[i])) || (str[i]=='_')){
                	continue;
                 }
                 else{
                 	flag1=true;
                        break;
                 }
        }
        if (flag1==false)
                 return 1;
        else
		return 0;
}
