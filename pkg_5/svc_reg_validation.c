                  #include <stdio.h>
#include <regex.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include "validation1.h"
#define MAX 2048
int  reg_svc_validation1(char *str)
{
	printf("\n entered reg_svc_validation");
    int i=0,len=0,rv=0;
    len=strlen(str);
    //str[len]='\0';
    const char* pattern = "[A-Z_]+:[a-zA-Z ]+,[a-zA-Z ]+,[a-zA-Z ]+,[a-zA-Z ]+,[a-zA-Z ]+,[0-9]";
    regex_t re;
	
    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) return 0;

    int status = regexec(&re, str, 0, NULL, 0);
    regfree(&re);
 	if (status == 0) {
		  rv=svc_length_checking1(str);
		  printf("\n in rv=%d",rv);
			if(rv==1)

				return 1;
			else
				return 0;
	}
     	else
		svc_validate_buffer1(str);         	
    
    
}    
void svc_validate_buffer1(char *cBuffer){
	bool flag1 = false,flag2=false,flag3=false,flag4=false,flag5=false,flag6=false;
	char *sName,*sType,*sStatus,*sSession,*sField,*command,*Uid;
	sName=(char*)malloc(MAX*sizeof(char));
	sType=(char*)malloc(MAX*sizeof(char));
	sStatus=(char*)malloc(MAX*sizeof(char));
	sField=(char*)malloc(MAX*sizeof(char));
	sSession=(char*)malloc(MAX*sizeof(char));
	command=(char*)malloc(MAX*sizeof(char));
	Uid=(char*)malloc(MAX*sizeof(char));
	memset(sName,0,sizeof(sName));
	memset(sType,0,sizeof(sType));
	memset(sStatus,0,sizeof(sStatus));
	memset(command,0,sizeof(command));
	memset(Uid,0,sizeof(Uid));
	memset(sField,0,sizeof(sField));
	memset(sSession,0,sizeof(sSession));
	int i=0,j=0,count=0,name=0,type=0,status=0,session=0,field=0,uid=0,iUid=0;
	if(cBuffer[0]!='\n'){
			
		while(cBuffer[i] != ':'){
			if(i<strlen(cBuffer)){
				command[j++] = cBuffer[i++];
				
			}
		}
		command[i]='\0';
		i++;
		j=0;

		while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
			sName[j++] = cBuffer[i++];

		sName[j]='\0';
		name=strlen(sName);
		i++;
		j=0;
		
		while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
        	                sType[j++] = cBuffer[i++];

                sType[j]='\0';
		type=strlen(sType);
                i++;
		j=0;


		while((cBuffer[i] != '\0') && (i<strlen(cBuffer)))
			sStatus[j++] = cBuffer[i++];

		sStatus[j]='\0';
		status=strlen(sStatus);
		j=0;

		while((cBuffer[i] != '\0') && (i<strlen(cBuffer)))
			sField[j++] = cBuffer[i++];

		sField[j]='\0';
		field=strlen(sField);
		j=0;

		while((cBuffer[i] != '\0') && (i<strlen(cBuffer)))
			sSession[j++] = cBuffer[i++];

		sSession[j]='\0';
		session=strlen(sSession);
		j=0;
		
		while((cBuffer[i] != '\n') && (i<strlen(cBuffer)))
                        Uid[j++] = cBuffer[i++];

                Uid[j]='\0';
		uid=strlen(Uid);
		
		if(strlen(sName)!=0){
			for(i=0;sName[i]!='\0';i++){
				if(isalpha(sName[i]) || sName[i]==' '){
					continue;
				}
				else{
					flag1=true;
					break;
				}
			}
		}
		else{
			
			printf("\n Please enter service name");
		}

		if(flag1==true)
			printf("\n Incorrect! Service name invalid,re-enter again");

		if(name>13)
			printf("\n Incorrect! Service Name should be maximum of 12 characters,re-enter again\n");


		 
		 if(strlen(sType)!=0){
                        for(i=0;sType[i]!='\0';i++){
                                if(isalpha(sType[i]) || sType[i]==' '){
                                        continue;
                                }
                                else{
                                        flag2=true;
                                        break;
                                }
                        }
                }
		else{
                        printf("\n Please enter service type");
                }


                if(flag2==true)
                        printf("\n Incorrect! service type invalid,re-enter again");

		 if(type>13)
                        printf("\n Incorrect!Service type should be maximum of 12 characters,re-enter again\n");


		 if(strlen(sStatus)!=0){
                        for(i=0;sStatus[i]!='\0';i++){
                                if(isalpha(sStatus[i]) || sStatus[i]==' '){
                                        continue;
                                }
                                else{
                                        flag3=true;
                                        break;
                                }
                        }
                }
		else{
                        printf("\n Please enter service status");
                }


                if(flag3==true)
                        printf("\n Incorrect! service status invalid,re-enter again");

		 if(status>13)
                        printf("\n  Incorrect! Service status should be maximum of 12 characters,re-enter again\n");

		if(strlen(sField)!=0){
                        for(i=0;sField[i]!='\0';i++){
                                if(isalpha(sField[i]) || sField[i]==' '){
                                        continue;
                                }
                                else{
                                        flag5=true;
                                        break;
                                }
                        }
                }
		else{
                        printf("\n Please enter service field");
                }


                if(flag5==true)
                        printf("\n Incorrect! service field invalid,re-enter again");

		 if(field>13)
                        printf("\n Incorrect!Service field should be maximum of 12 characters,re-enter again\n");


		if(strlen(sSession)!=0){
                        for(i=0;sSession[i]!='\0';i++){
                                if(isalpha(sSession[i]) || sSession[i]==' '){
                                        continue;
                                }
                                else{
                                        flag6=true;
                                        break;
                                }
                        }
                }
		else{
                        printf("\n Please enter service session");
                }


                if(flag6==true)
                        printf("\n Incorrect! service session invalid,re-enter again");

		 if(session>13)
                        printf("\n Incorrect!Service session should be maximum of 12 characters,re-enter again\n");



		 if(strlen(Uid)!=0){
                        for(i=0;Uid[i]!='\0';i++){
                                if(isdigit(Uid[i])){
                                        continue;

                                }
                                else{
                                        flag4=true;
                                        break;
                                }
                        }
			

                }
                else{
                        printf("\n Please enter UID");
			return 0;
                }
		
	if(flag4==true)
		printf("\n UID must be digits\n");	

                
		


	}
	free(sName);
        free(command);
        free(sType);
        free(sStatus);
        free(Uid);

     }


int svc_length_checking1(char *cBuffer){
	bool flag1 = false,flag2=false,flag3=false,flag4=false,flag5=false,flag6=false,flag7=false;
	char *sName,*sType,*sStatus,*command,*Uid,*sField,*sSession;
	sName=(char*)malloc(MAX*sizeof(char));
	sType=(char*)malloc(MAX*sizeof(char));
	sStatus=(char*)malloc(MAX*sizeof(char));
	sField=(char*)malloc(MAX*sizeof(char));
	sSession=(char*)malloc(MAX*sizeof(char));
	command=(char*)malloc(MAX*sizeof(char));
	Uid=(char*)malloc(MAX*sizeof(char));
	memset(sName,0,sizeof(sName));
	memset(sType,0,sizeof(sType));
	memset(sStatus,0,sizeof(sStatus));
	memset(command,0,sizeof(command));
	memset(Uid,0,sizeof(Uid));
	memset(sField,0,sizeof(sField));
	memset(sSession,0,sizeof(sSession));
	int i=0,j=0,count=0,name=0,type=0,status=0,session=0,field=0,uid=0,iUid=0;
	if(cBuffer[0]!='\n'){
			
		while(cBuffer[i] != ':'){
			if(i<strlen(cBuffer)){
				command[j++] = cBuffer[i++];
				
			}
		}
		command[i]='\0';
		i++;
		j=0;

		while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
			sName[j++] = cBuffer[i++];

		sName[j]='\0';
		name=strlen(sName);
		i++;
		j=0;

		while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
        	                sType[j++] = cBuffer[i++];

		
                sType[j]='\0';
		type=strlen(sType);

		i++;
		j=0;


		while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
			sStatus[j++] = cBuffer[i++];

		sStatus[j]='\0';
		status=strlen(sStatus);

		j=0;
		i++;
		

		while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
			sField[j++] = cBuffer[i++];

		sField[j]='\0';
		field=strlen(sField);

		j=0;
		i++;

		while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
			sSession[j++] = cBuffer[i++];

		sSession[j]='\0';
		session=strlen(sSession);

		j=0;
		i++;

		 while((cBuffer[i] != '\0') && (i<strlen(cBuffer)))
                        Uid[j++] = cBuffer[i++];

		

		iUid=atoi(Uid);
		uid=strlen(Uid);



		if((name<13) && (name>0)){
			flag1=true;
		}
		else
			printf("\n Incorrect! Service name should be maximum of 12 characters,re-enter again\n");	
		
		if((type<13) && (type>0)){
                        flag2=true;
                }

		else
			printf("\n Incorrect! Service type should be maximum of 12 characters,re-enter again\n");	
		
		if((status<13) && (status>0)){
                        flag3=true;
                }

		else
			printf("\n Incorrect! Service status should be maximum of 12 characters,re-enter again\n");
		
		if((field<13) && (field>0)){
                        flag6=true;
                }

		else
			printf("\n Incorrect! Service field should be maximum of 12 characters,re-enter again\n");

		if((session<13) && (session>0))
			flag7=true;
		else
			printf("\n Incorrect! Service session should be maximum of 12 characters,re-enter again\n");
		
		if(uid==4)
			flag4=true;
		else
			printf("\n Incorrect! UID must be 4 digits,re-enter again\n");	
		
		if((flag1==true) && (flag2==true) && (flag3==true) && (flag4==true) && (flag6==true) && (flag7==true))
			return 1;
		else
			return 0;
	}
	free(sName);
        free(command);
        free(sType);
        free(sStatus);
        free(Uid);

}
