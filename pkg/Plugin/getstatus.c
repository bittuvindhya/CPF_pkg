#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char* getstatus(){
        char *str=(char*)malloc(15*sizeof(char));
        memset(str,0,sizeof(str));
        strcpy(str,"available");
        return str;
}    

