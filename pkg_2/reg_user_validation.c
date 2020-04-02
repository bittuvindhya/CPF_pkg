#include<stdio.h>
#include<regex.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#define MAX 255
 
int reg_usr_validation(char *str)
{
    int i=0,len=0,rv=0;
    len=strlen(str);
    str[len]='\0';
    const char* pattern = "[A-Z_]+:[a-zA-Z]+,[a-zA-Z0-9_-].+@[a-z]+.[com]";
    regex_t re;
	
    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) return 0;

    int status = regexec(&re, str, 0, NULL, 0);
    regfree(&re);


	 if (status == 0) {
		 rv=length_checking(str);
		 if(rv==1)
			return rv;
		 else if(rv==2){
			 printf("\n Incorrect!,user name must be maximum of 12 characters,re-enter again \n");
			 return 0;
		 }
		 else if(rv==3){
			 printf("\n Incorrect! ,Please enter valid mail id,it must be maximum of 35 characters,re-enter again\n");
                         return 0;
		 }
		 else if(rv==4){
			 printf("\n Incorrect! ,user name must be maximum of 12 characters & mail id must be maximum of 35 characters,re-enter again\n");
		}
		else if(rv==5){
			printf("\n Invalid mail id\n");
			 return 0;
		 }
     	 }
	
    	 else{
		validate_buffer(str);         	
    	 }
    
}    
void validate_buffer(char *cBuffer){
	bool flag1 = false,name_flag=false,mailid_flag=false;
	char *cName,*cMailid,*command;
	int i=0,j=0,name_len=0,mailid_len=0;
	cName=(char *)malloc(MAX*(sizeof(char)));
	cMailid=(char *)malloc(MAX*(sizeof(char)));
	command=(char *)malloc(MAX*(sizeof(char)));
	memset(cName, 0, sizeof(cName));
	memset(cMailid, 0, sizeof(cMailid));
	memset(command, 0, sizeof(command));
	if(cBuffer[0]!='\n'){
		while(cBuffer[i] != ':'){
			command[i] = cBuffer[i];
			i++;
		}

		command[i]='\0';
		i++;

		if(i<strlen(cBuffer)){
			while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
				cName[j++] = cBuffer[i++];
			name_len=strlen(cName);
		}	
		else{
			name_flag=true;
		}


		if(name_flag==false){
			if((name_len<13) && (name_len>0)){
				cName[j]='\0';
				i++;	
			}
			else{
				printf("\n Incorrect!,Username must be maximum of 12 characters,re-enter again\n");
			}
		}
		j=0;

		if(i<strlen(cBuffer)){
			while((cBuffer[i] != NULL) && (i<strlen(cBuffer))){
				cMailid[j++] = cBuffer[i++];
			}
			cMailid[j]='\0';
			mailid_len=strlen(cMailid);
		}
		else{
			mailid_flag=true;
		}
		if(mailid_flag==false){
			if((mailid_len<38) && (mailid_len>0)){
                	        email_validation(cMailid);
                	}
	                else{
        	                printf("\n Incorrect! Mail id must be maximum of 35 characters,re-enter again\n");
                	}
		}




		if(name_flag==false){

			for(i=0;cName[i]!='\0';i++){
                                if(isalpha(cName[i])){
                                        continue;
                                }
                                else{
                                        flag1=true;
                                        break;
                                }
                        }
		}

		if(flag1==true)
                        printf("\nSorry,Invalid Username\n");

		  if((name_flag==true) && (mailid_flag==true))
                        printf("\n Please enter valid username and mail id\n");
                  else if((name_flag==true) && (mailid_flag==false))
                        printf("\n Please enter username\n");
                  else if((mailid_flag==true) && (name_flag==false))
                        printf("\n Please enter mail id\n");

	}
	free(cName);
	free(cMailid);
	free(command);
     }


void email_validation(char *mail)
{
	    const char* pattern = "[a-zA-Z0-9_-]+@[a-z]+.com";
	    regex_t re;
	    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) return 0;
	    
	    int status = regexec(&re, mail, 0, NULL, 0);
	    regfree(&re);
	    if(isalpha(mail[0]) != 0)
		    status=1;
	    
	    if (status != 0)
        	printf("\n Please enter valid mail id\n");
}
	
int length_checking(char *cBuffer)
{
	int name_len=0,mailid_len=0,i=0,j=0,k=0,z=0,at_count=0,val=0;
	bool name=false,mailid=false,at_mail=false,com_flag=false;
	char *cName,*cMailid,*command,*buff,*ret;
	cName=(char *)malloc(MAX*(sizeof(char)));
        cMailid=(char *)malloc(MAX*(sizeof(char)));
        command=(char *)malloc(MAX*(sizeof(char)));
	ret=(char *)malloc(MAX*(sizeof(char)));
	buff=(char *)malloc(MAX*(sizeof(char)));
        memset(cName, 0, sizeof(cName));
        memset(cMailid, 0, sizeof(cMailid));
        memset(command, 0, sizeof(command));
	memset(buff, 0, sizeof(buff));
	memset(ret, 0, sizeof(ret));

	if(cBuffer[0]!='\n'){
                while(cBuffer[i] != ':'){
                        command[i] = cBuffer[i];
                        i++;
                }

                command[i]='\0';
                i++;

                if(i<strlen(cBuffer)){
                        while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
                                cName[j++] = cBuffer[i++];
                        name_len=strlen(cName);
                }

		 cName[j]='\0';
                 i++;
		
		 j=0;

                if(i<strlen(cBuffer)){
                        while((cBuffer[i] != NULL) && (i<strlen(cBuffer))){
                                cMailid[j++] = cBuffer[i++];
                        }
                        mailid_len=strlen(cMailid);
                }

		for(k=0;k<strlen(cMailid);k++){
			if(cMailid[k]=='@'){
				val=k;
				at_count++;
			}
		}
		j=0;
		while(cMailid[val] != NULL)
			buff[j++]=cMailid[val++];


		
		ret=strchr(buff,'.');
				int a =strcmp(ret,".com");
		if((strcmp(ret,".com")) == 10 )
			com_flag=true;	
		
		if(at_count==1)
			at_mail=true;


		if((name_len<13) && (name_len>0))
			name=true;
		if((mailid_len<38) && (mailid_len>0))
			mailid=true;

            if(isalpha(cMailid[0]) != 0)
                    mailid=true;
            else{
                    mailid=false;
            }


		if((name==true) && (mailid==true) && (at_mail==true) && (com_flag==true))
			return 1;
		else if((name==false) && (mailid==true))
			return 2;
		else if((name==true) && (mailid==false))
			return 3;
		else if((name==false) && (mailid==false))
			return 4;
		else if((at_mail==false) || (com_flag==false))
			return 5;
	}
	free(cName);
        free(cMailid);
        free(command);

}
