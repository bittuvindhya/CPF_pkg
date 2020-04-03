#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char* gettype(){
        char *str=(char*)malloc(15*sizeof(char));
        memset(str,0,sizeof(str));
        strcpy(str,"Parser");
        return str;
}    

