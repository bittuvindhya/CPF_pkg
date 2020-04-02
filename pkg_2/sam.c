#include<stdio.h>
#include<regex.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#define MAX 255
 
int reg_usr_validation()
{
    int i=0,len=0,rv=0;
    char str[100];
    printf("\n enter mail id");
    scanf("%s",str);
    len=strlen(str);
    str[len]='\0';
    const char* pattern = "^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$";
    regex_t re;
	
    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) return 0;

    int status = regexec(&re, str, 0, NULL, 0);
    printf("\n status =%d",status);
    regfree(&re);


	 if (status == 0) {
		 printf("\n matched");
	}
	 else
		 printf("\n not matched");
}
void main(){
	reg_usr_validation();
}
