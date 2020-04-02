#include <stdio.h>
#include <regex.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#define MAX 255
int  svc_list_validation(char *str,int uid)
{
    int i=0,len=0,rv=0;
    len=strlen(str);
    str[len]='\0';
    const char* pattern = "[A-Z_]+:[0-9]+,[a-zA-Z0-9]";
    regex_t re;
	
    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) return 0;

    int status = regexec(&re, str, 0, NULL, 0);
    regfree(&re);
 	if (status == 0) {
		  rv=svc_list_length_checking(str,uid);
			if(rv==1)

				return 1;
			else
				return 0;
	}
     	else
		svc_list_validate_buffer(str,uid);         	
    
    
}    
int  svc_list_validate_buffer(char *cBuffer,int uid){
	bool flag1 = false,flag2=false;
	char *scategory,*command,*Uid;
	scategory=(char*)malloc(MAX*sizeof(char));
	command=(char*)malloc(MAX*sizeof(char));
	Uid=(char*)malloc(MAX*sizeof(char));
	memset(scategory,0,sizeof(scategory));
	memset(command,0,sizeof(command));
	memset(Uid,0,sizeof(Uid));
	int i=0,j=0,count=0,category=0,iUid=0;
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
                        scategory[j++] = cBuffer[i++];

		category=strlen(scategory);
		
		if(strlen(scategory)!=0){
                        for(i=0;scategory[i]!='\0';i++){
                                if(isalpha(scategory[i]) || scategory[i]==' '){
                                        continue;
                                }
                                else{
                                        flag2=true;
                                        break;
                                }
                        }
                }
		else{
                        printf("\n Please enter service status\n");
                }


                if(flag2==true)
                        printf("\n Sorry,service status invalid\n");

		 if(category>13)
                        printf("\n Incorrect! ,Service category should be maximum of 12 characters,re-enter again\n");


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
	/*free(scategory);
	free(command);
	free(Uid);*/
     }


int svc_list_length_checking(char *cBuffer,int reg_uid){
	bool flag1 = false,flag2=false,flag3=false;
	char *scategory,*command,*Uid;
	scategory=(char*)malloc(MAX*sizeof(char));
	command=(char*)malloc(MAX*sizeof(char));
	Uid=(char*)malloc(MAX*sizeof(char));
	memset(scategory,0,sizeof(scategory));
	memset(command,0,sizeof(command));
	memset(Uid,0,sizeof(Uid));
	int i=0,j=0,count=0,category=0,uid=0,iUid=0;
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
                        scategory[j++] = cBuffer[i++];

		category=strlen(scategory);

		iUid=atoi(Uid);
		
		if((category<13) && (category>0))
			flag1=true;
		else
			printf("\n Incorrect! ,service category should be maximum of 12 characters, re-enter again\n");

		if(uid==4)
			flag2=true;
		else
			printf("\n Incorrect! ,UID must be 4 digits, re-enter again\n");	
		
		if(iUid==reg_uid)
			flag3=true;
		else
			printf("\n Incorrect! ,Please enter your registered UID, re-enter again\n");
		
		if((flag1==true) && (flag2==true) && (flag3==true))
			return 1;
		else
			return 0;
	}
	/*free(scategory);
	free(command);
	free(Uid);*/
}
