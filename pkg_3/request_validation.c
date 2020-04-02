#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "cpfapi.h"
#define MAX 2048

int request_validation(char *buf,int *req_type,char *req){

	int i = 0;
	char *str,*str1,*buff;
	//buff=(char*)malloc(MAX*sizeof(char));
	//str1=(char*)malloc(MAX*sizeof(char));
	//printf("\n buf=%s ,req_type=%d ,req_input=%s",buf,*req_type,req_input);
	printf("\nrequest_validation entering");
	//strcpy(buff,buf);
	req_input= strchr(buf, ':');
	req_input++;
		printf("\n   req_input->%s",req_input);
	//strcpy(req_input,str1);
	//printf("\nreq_input->%s",req_input);
	if(strlen(buf) != 0){
                str=strtok(buf,":");
		
                do
                {
			printf("\nstr-->%s",str);
                    
                                switch (i) {
					case T_NONE:
						break;
                                        case T_REGISTER_USER:
						printf("\n T_REGISTER_USER = %d , i =%d",T_REGISTER_USER,i);
                                        	if(strncmp(str,"REG_USR",7)==0)
							*req_type=T_REGISTER_USER;
						else
							printf("Not entering REG_USR");
						break;
					case T_REG_SVC:
						
						if(strncmp(str,"REG_SVC",7)==0){
							printf("\n entered REG_SVC");	
							*req_type = T_REG_SVC;
							printf("\n *req_type %d",*req_type);
						}
						else
							printf("Not entering REG_SVC");
						break;
                                        case T_GET_SVC_LIST:
                                        	if(strncmp(str,"GET_SVC_LIST",12)==0)
							*req_type=T_GET_SVC_LIST;
						else
							printf("Not entering T_GET_SVC_LIST");
						break;
                                        case T_SUBSCRIBE_SVC:
                                        	if(strncmp(str,"SUBSCRIBE",9)==0)
							*req_type=T_SUBSCRIBE_SVC;
						else
							printf("Not entering SUBSCRIBE");
						break;
					case T_START_SESSION:
                                               if(strncmp(str,"START_SESSION",13)==0)
							*req_type=T_START_SESSION;
						else
							printf("Not entering START_SESSION");
						break;
                                        case T_SVC_INPUT:
                                                if(strncmp(str,"INPUT",5)==0)
							*req_type=T_SVC_INPUT;
						else
							printf("Not entering INPUT");
						break;
                                        case T_END_SESSION:
						printf("\n entering into end session i=%d",i);
                                                if(strncmp(str,"END_SESSION",11)==0)
							*req_type=T_END_SESSION;
						else
							printf("Not entering END_SESSION");		
						break;
                                        default :
                                                break;
                                }
                                i++;
                       
		printf("\n i=%d",i);
		} while(i < 8);
		
		
		
		return 0;
	}
	else
		return -1;
}
/*void main(){
char buf[] = "REG_SVC:Json,Parser ,available,ifconfig,interactive,1001";
//strcpy(buf,"REG_SVC:Json");
int req_type = 0;
printf("\nbuff  %s",buf);
int rv =0;
rv = request_validation(buf,&req_type,req_input);
printf("\n %d",req_input);
printf("\nreturned %d",rv);
printf("\n *req_type %d",req_type);
printf("\n   req_input->%s",req_input);
}*/	
