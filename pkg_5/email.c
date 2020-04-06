#include <stdio.h>
#include <regex.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
 
int validation(char* str)
{
    int i=0,len=0;
    str=(char*)malloc(100*sizeof(char));
    len=strlen(str);
    str[len]='\0';
    printf("\n len=%d",len);
    const char* pattern = "[A-Z_]+:[a-zA-Z]+,[a-zA-Z0-9_-].+@[a-z]+.com";
    regex_t re;
	
    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) return 0;

    int status = regexec(&re, str, 0, NULL, 0);
    regfree(&re);
	if(len==0)
		printf("\n no input");

	else if (status == 0) {
	       	//printf("\n%s matching",str);
		return 1;
     }
	
    else{
		validate_buffer(str);         	
    }
    
}    
void validate_buffer(char* cBuffer){
	bool flag1 = false;
	char cName[100],cMailid[100],command[100];
	int i=0,j=0;
	printf("cbuffer=%s",cBuffer);
	if(cBuffer[0]!='\n'){

		while(cBuffer[i] != ':'){
			command[i] = cBuffer[i];
			i++;
		}

		command[i]='\0';
		//printf("\n command=%s",command);
		i++;

		while(cBuffer[i] != ',')
			cName[j++] = cBuffer[i++];

		cName[j]='\0';
		i++;
		//printf("\ncName =>%s",cName);
		j=0;

		while(cBuffer[i] != '\0')
			cMailid[j++] = cBuffer[i++];

		cMailid[j]='\0';
		//printf("\ncMailid =>%s",cMailid);

		if(strlen(command)!=0){
			command_validation(command);

		}


		if(strlen(cName)!=0){
			for(i=0;cName[i]!='\0';i++){
				if(isalpha(cName[i]) || cName[i]==' '){
					continue;
				}
				else{
					flag1=true;
					break;
				}
			}
		}

		if(flag1==true)
			printf("\nname invalid");
		 
		email_validation(cMailid);
	}
     }

void command_validation(char str[100])
{
	int status=0,i=0,jee=0;
	int len=strlen(str);
	
   	for(i=0;i<len;i++){
		    if (isupper(str[i]) || (str[i]=='_')){
			jee++;
		    }

		    else
			   status++;
			        
        }

        if(status>0)
		   printf("\n command invalid");
      

}

void email_validation(char mail[100])
{
    printf("\nmail id %s",mail);
    const char* pattern = "[a-zA-Z0-9_-].+@[a-z]+.com";
    regex_t re;

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) return 0;

    int status = regexec(&re, mail, 0, NULL, 0);
    regfree(&re);

    if (status != 0)
        printf("%s invalid mail id",mail);
    
}
