#include <stdio.h>
#include <regex.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#define MAX 255
int  subscribe_validation(char *str,int uid)
{
    int i=0,len=0,rv=0;
    len=strlen(str);
    str[len]='\0';
    const char* pattern = "[A-Z_]+:[0-9]+,[0-9]";
    regex_t re;
	
    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) return 0;

    int status = regexec(&re, str, 0, NULL, 0);
    regfree(&re);
 	if (status == 0) {
		  rv=subscribe_length_checking(str,uid);
			if(rv==1)

				return 1;
			else
				return 0;
	}
     	else
		subscribe_validate_buffer(str,uid);         	
    
    
}    
int  subscribe_validate_buffer(char *cBuffer,int uid){
	bool flag1 = false,flag2=false;
	char *sid,*command,*Uid;
	sid=(char*)malloc(MAX*sizeof(char));
	command=(char*)malloc(MAX*sizeof(char));
	Uid=(char*)malloc(MAX*sizeof(char));
	memset(sid,0,sizeof(sid));
	memset(command,0,sizeof(command));
	memset(Uid,0,sizeof(Uid));
	int i=0,j=0,count=0,sid_category=0,iUid=0;
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
			Uid[j++] = cBuffer[i++];

		Uid[j]='\0';
		uid=strlen(Uid);
		j=0;
		i++;
		
		while((cBuffer[i] != '\0') && (i<strlen(cBuffer)))
                        sid[j++] = cBuffer[i++];

		sid_category=strlen(sid);
		
		if(strlen(sid)!=0){
                        for(i=0;sid[i]!='\0';i++){
                                if(isdigit(sid[i])){
                                        continue;
                                }
                                else{
                                        flag2=true;
                                        break;
                                }
                        }
                }
		else{
                        printf("\n Please enter SID\n");
                }


                if(flag2==true)
                        printf("\n Sorry,SID invalid\n");

		 if(sid_category==5)
                        printf("\n Incorrect! ,SID should be maximum of 4 digit,re-enter again\n");


		 if(strlen(Uid)!=0){
                        for(i=0;Uid[i]!='\0';i++){
                                if(isdigit(Uid[i])){
                                        continue;

                                }
                                else{
                                        flag1=true;
                                        break;
                                }
                        }
			

                }
                else{
                        printf("\n Please enter UID\n");
                }
		
		

                if(flag1==true)
                        printf("\n Sorry,invalid UID\n");
		if(uid!=4)
			printf("\n Incorrect! ,UID must be 4 digit ,please enter valid uid,re-enter again.\n");


	}
	/*free(sid);
	free(command);
	free(Uid);*/
     }


int subscribe_length_checking(char *cBuffer,int reg_uid){
	bool flag1 = false,flag2=false,flag3=false,uid_digit=false,sid_digit=false;
	char *sid,*command,*Uid;
	sid=(char*)malloc(MAX*sizeof(char));
	command=(char*)malloc(MAX*sizeof(char));
	Uid=(char*)malloc(MAX*sizeof(char));
	memset(sid,0,sizeof(sid));
	memset(command,0,sizeof(command));
	memset(Uid,0,sizeof(Uid));
	int i=0,j=0,count=0,sid_category=0,uid=0,iUid=0;
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
			Uid[j++] = cBuffer[i++];

		Uid[j]='\0';
		uid=strlen(Uid);
		j=0;
		i++;
		
		 while((cBuffer[i] != '\0') && (i<strlen(cBuffer)))
                        sid[j++] = cBuffer[i++];

		sid_category=strlen(sid);
		
		iUid=atoi(Uid);

                 for(i=0;Uid[i]!='\0';i++){
                          if(isdigit(Uid[i])){
				  
                                   continue;
                           }
                           else{
				                              
				uid_digit=true;
                                 break;
                           }
                  }
		
		for(i=0;sid[i]!='\n';i++){
                          if(isdigit(sid[i])){
				
                                   continue;
                           }
                           else{
				
                                 sid_digit=true;
                                 break;
                           }
                  }

                
		if(sid_category==5)
			flag1=true;
		else
			printf("\n Incorrect! ,SID should be maximum of 4 digit, re-enter again\n");

		if(uid==4)
			flag2=true;
		else
			printf("\n Incorrect! ,UID must be 4 digits, re-enter again\n");	
		
		if(iUid==reg_uid)
			flag3=true;
		else
			printf("\n Incorrect! ,Please enter your registered UID, re-enter again\n");
		if((sid_digit==true) || (uid_digit==true))		
			printf("\n Invalid SID or UID\n");

		if((flag1==true) && (flag2==true) && (flag3==true) && (uid_digit==false) && (sid_digit==false))
			return 1;
		else
			return 0;
	}
	/*free(sid);
	free(command);
	free(Uid);*/
}
