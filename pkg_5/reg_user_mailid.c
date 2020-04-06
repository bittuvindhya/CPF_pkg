#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include "cpfapi.h"

int iUid=1000;
/*int count=0;
int regid;
int uid_retrive() 
{ 
	char buff[1024],*str;
     	int count=0,last=0,i=0;
     	FILE *fp = fopen("uid_table.csv","r");
     	char* token;
     	while(fgets(buff,1024,(FILE*)fp)){
		count++;
	}
     	fclose(fp);
     	last=--count;
     	fp = fopen("uid_table.csv","r");
	count=0;
     	while(fgets(buff,1024,(FILE*)fp)){
		count++;
	     	printf("%s",buff);
	     	if(count==last){
			token=strtok(buff,",");
			regid=atoi(token);
			printf("token : %s ,regid :%d",token ,regid);
			/*for(;i<=3;i++)
				str[i]=token[i];
			str[i]='\0';
			break;	
	     	}
		//break;
	}
	printf("reg :%d",regid);
	return regid;
}*/
int uim_reg_usr( char *cBuffer ){
	FILE *fp;
	bool flag1 = false ,flag2 = false;
	int i = 0,j = 0,iuid = 0;
	char cName[100],cMailid[100],cfBuffer[256],*str;
	str=(char*)malloc(5*sizeof(char));	
	if(strlen(cBuffer)!=0){
	while(cBuffer[i] != ',')
		cName[i++] = cBuffer[i];
	cName[i]='\0';
	i++;
	while(cBuffer[i] != '\0')
		cMailid[j++] = cBuffer[i++];
	cMailid[j]='\0';
	/*if(strlen(cName)!=0){
		for(i=0;cName[i]!='\0';i++){
			if(isalpha(cName[i]) || (cName[i]==' ' && i!=0)){
				continue;
			}
			else{
				flag1=false;
				break;
			}
		}
	}
	else{
		flag1=false;
	}
	count=0;
	if(strlen(cMailid)!=0){
		for(i=0;cMailid[i]!='\0';i++){
			if(cMailid[i]=='@'){
				j=i;
				count++;
			}
			if(cMailid[i]=='.' && i>(j+2) && count==1){
				count++;
			}
		}
		if(count>2){
                	printf("%c",cMailid[i]);
			flag2=false;
		}	
		else{
			
			for(i=0;i<j;i++){
				if(isalnum(cMailid[i]) || ((cMailid[i]=='-' || cMailid[i]=='_' || cMailid[i]=='.' || cMailid[i]==' ') && i!=0))
					continue;
				else{
					flag2=false;
					break;
				}
			}
			for(i=j+1;(cMailid[i]!='.' && flag2);i++){
				if(isalpha(cMailid[i]))
					continue;
				else{
					flag2=false;
				}
			}
			i++;
			for(;(cMailid[i]!='\0' && flag2);i++){
				if(isalpha(cMailid[i]))
					continue;
				else{
					flag2=false;
				}	
			}	
		}
	}
	else{
		flag2=false;
	}
	
	if(flag1 && flag2){
		flag2=false;
	*/	
	iUid=uid_retrive();	
	fp = fopen("uid_table.csv","r+");
		while(fgets(cfBuffer,100,fp)){
			if (strstr(cfBuffer,cMailid)){
				str=strtok(cfBuffer,",");
				iuid=atoi(str);
				flag2=true;
				break;
			}
		}
		fclose(fp);
		if(flag2 == false){
			fp = fopen("uid_table.csv","a+");
			if (fp == NULL){
				printf("Can't open a file");
				exit(0);
			}
			fprintf(fp,"%d,%s,%s\n",++iUid,cName,cMailid);
			fclose(fp);
			return iUid;
		}
		return iuid+5000;
	}
	}
 	/*	
	else if(!flag1 && !flag2)
		printf("\nInvalid name and mailid\n");
	else if(!flag1)
		printf("\nInvalid name\n");
	else if(!flag2)
		printf("Invalid mailid\n");
	}
	else{
		printf("Invalid name and mailid\n");
	}*/


/*void main()
{
	char *str;
	str=(char*)malloc(100*sizeof(char));
	do{
		printf("enter name,mailid\n");
		gets(str);
		uim_reg_usr(str); 
	}while(1);
/*printf("falg2=>%d",flag2);
				str = strtok(cfBuffer, ",");
				for(i=0;i<=3;i++)
					str1[i]=str[i];
				str1[i]='\0';		
				printf("Data from the file: %s\n",str1);*/

