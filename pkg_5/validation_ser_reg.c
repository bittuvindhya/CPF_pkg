/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <regex.h>
#include<ctype.h>
#include<stdbool.h>
#include "validation.h"
#define MAX 2048

int main_validation(char *cBuffer,int uid){
	int len=0,i=0,val_command=0,l=0,count=0,k=0;
	static int reg_user=0 ,sub_count = 0;
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
				return 0;
			}
			if(strncmp(command,"REG_USR",7)==0){
				if(reg_user == 0){				
					count=reg_usr_validation(cBuffer);
					if(count==1){
						reg_user++;
					}
				}
				else{
					printf("\nalready registered user ");
					return 0;
				}
				if(reg_user<=1)
					return count;
				else
					printf("\n Your already registered user,cannot register again\n");
			}
	
			else if(strncmp(command,"GET_SVC_LIST",12)==0){
				if(reg_user>=1)
					return svc_list_validation(cBuffer,uid);
				else
					printf("\n First you need to register,enter REG_USR command\n");
			}
			else if(strncmp(command,"SUBSCRIBE",9)==0){
				if(reg_user>=1){
					count = subscribe_validation(cBuffer,uid);
					if(count == 1)
						sub_count++;
					if(sub_count >= 1)
						return count;
				}
				else
					printf("\n First you need to register,enter REG_USR command\n");
			}
			else if(strncmp(command,"START_SESSION",13)==0){
				if(reg_user>=1 && sub_count >=1)
					return start_session_validation(cBuffer,uid);

				else if(sub_count < 1)
					printf("\nPlease subscribe any service , so that you can start a session for a service \n");

				else
					printf("\n First you need to register,enter REG_USR command \n");

			}
			else if(strncmp(cBuffer,"ifconfig",8)==0){
                		if(reg_user>=1)
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
}*/
/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <regex.h>
#include<ctype.h>
#include<stdbool.h>
#include "validation.h"
#define MAX 2048

int main_validation(char *cBuffer,int uid){
    int len=0,i=0,val_command=0,l=0,count=0,k=0,len_buff=0,count_colon=0,count_comma=0,sub_val_count = 0;
    static int reg_user=0,sub_count = 0,sub_output = 0;
    char *command = NULL,*cbuffer = NULL,*buff = NULL,*sub_buffer=NULL;
    char buffer[MAX];
    bool flag1=false;
    command=(char*)malloc(MAX*sizeof(char));
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
        len_buff=strlen(buffer);

        for(i=0;i<len_buff;i++){
            if(buffer[i] == ':')
                count_colon++;
            if(buffer[i] == ',')
                count_comma++;
        }
        //printf("\n count colon=%d",count_colon);
        //printf("\n count comma=%d",count_comma);
        if(count_colon == 1){
            command=strtok(buffer,":");
            l=strlen(command);
            //if(flag1==false){
            command[l]='\0';
            val_command=command_checking(command);
            if(val_command > 0 ){
                command[l]='\0';
            }
	else if(srtcmp(cBuffer,"you are successfully subscribed",31)==0){
			sub_output++;
	}
       else{
                printf("\n Please Enter valid command\n");
                return 0;
       }
	if(strncmp(command,"REG_USR",7)==0){
                count = 0;
                //printf("%d",reg_user);
                if((count_comma == 1) && (reg_user == 0)){
                    count=reg_usr_validation(cBuffer);
                    if(count==1){
                        reg_user++;
                    }
                    if(reg_user<=1)
                        return count;
                }
		else if(strncmp(command,"REG_USR",7)==0){
                	printf("\n Your already registered user,cannot register again\n");
                    	return 0;
                }
                else{
              		printf("\n Please,enter correct username and mail id\n");
                    	return 0;
                }
	}        

		else if(strncmp(command,"GET_SVC_LIST",12)==0){
                	if(count_comma == 1){
                   		 if(reg_user==1)
                        		return svc_list_validation(cBuffer,uid);
                    		else{
                       			 printf("\n First you need to register,enter REG_USR command\n");
                       			 return 0;
                   		 }
               		 }
                	else{
                  		printf("\n Please enter registered UID and category\n");
                    		return 0;
                	}
		}
		else if(strncmp(command,"SUBSCRIBE",9)==0){
               		 if(count_comma == 1){
                		if(reg_user==1){
					sub_val_count  = subscribe_validation(cBuffer,uid);
					if(sub_val_count  == 1)
						sub_count++;
					if(sub_count <= 1)
						return sub_val_count ;
				}

                    		else{
                        	printf("\n First you need to register,enter REG_USR command\n");
				return 0;
				}
               		}
               		else{
                    		printf("\n Please enter registered UID and service id\n");
                   		return 0;
               		}

            	}
		
		else if(strncmp(command,"START_SESSION",13)==0){
                	if(count_comma == 1){
                		if(reg_user==1 && sub_count >=1 && sub_output >=1)
                        		return start_session_validation(cBuffer,uid);
				else if(sub_count < 1){
					printf("\nPlease subscribe any service , so that you can start a session for a service \n");
					return 0;
			}
                    	else{
                        	printf("\n First you need to register,enter REG_USR command\n");
				return 0;
			}
                }
		
                else{
                	printf("\n Please enter registered UID and service id\n");
			return 0;

            }

	else if(strncmp(cBuffer,"ifconfig",8)==0){
                if(reg_user==1)
                	return ifconfig(cBuffer);
                else{
              		printf("\n First you need to register,enter REG_USR command\n");
			return 0;
		}
        }
        else if(count_colon !=1){
                printf("\n Sorry,Please check your command \n");
                return 0;
            }
        else{
            printf("\n Please enter correct username and mailid\n");
            return 0;
        }
}

free(command);
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
}*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <regex.h>
#include<ctype.h>
#include<stdbool.h>
#include "validation.h"
#define MAX 2048

int main_validation(char *cBuffer,int uid){
    int len=0,i=0,val_command=0,l=0,count=0,k=0,len_buff=0,count_colon=0,count_comma=0,sub_rv = 0;
    static int reg_user=0,sub_count = 0,sub_output = 0;
    char *command = NULL,*cbuffer = NULL,*buff = NULL;
    char buffer[MAX];
    bool flag1=false;
    command=(char*)malloc(MAX*sizeof(char));
    len=strlen(cBuffer);
    //printf("\n buffer=%s,uid=%d",cBuffer,uid);
    //printf("\n length of buffer =%d",len);
    if(strncmp(cBuffer,"QUIT",4) == 0){
        if ((strlen(cBuffer)-1) == 4)
            return 10;
        else{
            printf("\nSorry,Please check your command \n");
            return 0;
        }
    }
    if(strncmp(cBuffer,"ifconfig",8)==0)
        val_command = 2 ;
    if(len==1)
        printf("\n Please,Enter command\n");
   else if(strncmp(cBuffer,"you are successfully subscribed",31)==0){	
	sub_output = 1;	
    }
    else{
        strcpy(buffer,cBuffer);
        len_buff=strlen(buffer);

        for(i=0;i<len_buff;i++){
            if(buffer[i] == ':')
                count_colon++;
            if(buffer[i] == ',')
                count_comma++;
        }
        //printf("\n count colon=%d",count_colon);
        //printf("\n count comma=%d",count_comma);
        if((count_colon == 1)){
            command=strtok(buffer,":");
            l=strlen(command);

            //if(flag1==false){
            command[l]='\0';
            val_command=command_checking(command);
            if((val_command > 0) && (l<=13)){
                command[l]='\0';
            }
            else{
                printf("\n Please Enter valid command\n");
                return 0;
            }

            if(strncmp(command,"REG_USR",7) == 0){
                if (l == 7){
                    count = 0;
                    if((count_comma == 1) && (reg_user == 0)){
                        count=reg_usr_validation(cBuffer);
                        if(count==1){
                            reg_user++;
                        }
                        if(reg_user<=1)
                            return count;
                    }
                    else if((strncmp(command,"REG_USR",7)==0)&&(reg_user == 1)){
                        printf("\n Your already registered user,cannot register again\n");
                        return 0;
                    }
                    else{
                        printf("\n Please,enter correct username and mail id \n");
                        return 0;
                    }
                }else{
                    printf("\n Sorry,Please check your command \n");
                                return 0;
                }
            }        

            else if(strncmp(command,"GET_SVC_LIST",12)==0) {
                    if (l == 12){
                        if(count_comma == 1){
                        
                            if(reg_user==1)
                                return svc_list_validation(cBuffer,uid);
                            else{
                                printf("\n First you need to register,enter REG_USR command\n");
                                return 0;
                            }
                        }
                        else{
                            printf("\n Please enter registered UID and category\n");
                            return 0;
                        }
                    }else{
                        printf("\n Sorry,Please check your command \n");
                                        return 0;
                    }
            }
                    
            else if(strncmp(command,"SUBSCRIBE",9)==0){
                if (l == 9){	
                    if(count_comma == 1){
                        if(reg_user==1){
                        	sub_rv=subscribe_validation(cBuffer,uid);	
				if(sub_rv == 1)
					sub_count++;
				return sub_rv;
                        }
			else{
                            printf("\n First you need to register,enter REG_USR command\n");
			    return 0;
			}
                    }else{
                        printf("\n Please enter registered UID and service id\n");
                        return 0;
                    }
                }else{
                        printf("\n Sorry,Please check your command \n");
                                        return 0;
                }

            }
            else if(strncmp(command,"START_SESSION",13)==0){
                if (l == 13){
                    if(count_comma == 1){
                        if(reg_user==1 && sub_count >= 1 && sub_output == 1)
                            return start_session_validation(cBuffer,uid);

			else if(sub_count < 1 || sub_output < 1){
			printf("\n Please subscribe to a service to start a session\n");
			return 0;
		   	}
                        else{
                            printf("\n First you need to register,enter REG_USR command\n");
			    return 0;
			}
                    }
                    else{
                        printf("\n Please enter registered UID and service id\n");
                        return 0;
                    }
                }    
                else{
                    printf("\n Sorry,Please check your command \n");
                                return 0;
                }
            }

            else if(strncmp(cBuffer,"ifconfig",8)==0){
                          if(reg_user==1)
                                  return ifconfig(cBuffer);
                else
                                printf("\n First you need to register,enter REG_USR command\n");

                }
            else{
                printf("\nSorry,Please check your command\n");
                return 0;
            }
        }
        else if(count_colon !=1) {
                printf("\n Sorry,Please check your command \n");
                return 0;
            }

        else{
            printf("\n Please enter correct username and mailid\n");
            return 0;
        }
}

    free(command);
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


