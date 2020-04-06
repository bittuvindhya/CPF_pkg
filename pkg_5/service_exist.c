#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "cpfapi.h"
#include<fcntl.h>

#define  SVC_LIST_DB    "/home/vindhya/pkg_4444/service_reg_table.csv"

struct get_list list[100];

int service_exist(char *cBuffer){
	char buff[1024],*str_name,*str_type,*str_sessiontype,*str_status,*str_field,*str_uid,*token;
	str_name=(char*)malloc(sizeof(char));
	str_type=(char*)malloc(sizeof(char));
	str_field=(char*)malloc(sizeof(char));
	str_sessiontype=(char*)malloc(sizeof(char));
	str_status=(char*)malloc(sizeof(char));
	str_uid=(char*)malloc(sizeof(char));
      	int count=0,lsid=0,i=0,sid=3000,j = 0;
	printf("cbuffer  --> %s",cBuffer);
	printf("\n entered in service_exist");
	cBuffer[strlen(cBuffer)]='\0';
	int fd = open(SVC_LIST_DB, O_CREAT|O_RDWR|O_APPEND);
        int bytes_read = 0;
	int rec_index=0;

	while((bytes_read = read(fd, (void *)&list[rec_index], sizeof(struct get_list))) != 0){
                        rec_index++;
        }

	for(i=0;i<rec_index;i++){
                        fprintf(stderr,"INFO: service DATA in service_exist (%d)\n",i);
                        fprintf(stderr,"      -----> NAME   : (%s)\n",list[i].name);
                        fprintf(stderr,"      -----> TYPE: (%s)\n",list[i].type);
                        fprintf(stderr,"      -----> field  : (%s)\n",list[i].field);
			fprintf(stderr,"      -----> iUid  : (%s)\n",list[i].iUid);
 	}
	i=0;
	while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
		str_name[j++]=cBuffer[i++];
	str_name[j]='\0';
	printf("\nstr name --> %s ",str_name);
	i++;
	j=0;
	while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
		str_type[j++]=cBuffer[i++];
	str_type[j]='\0';
	printf("\nstr type --> %s ",str_type);
	i++;
	j=0;
	while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
		str_status[j++]=cBuffer[i++];
	str_status[j]='\0';
	printf("\nstr status--> %s ",str_status);
	i++;
	j=0;
	while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
		str_field[j++]=cBuffer[i++];
	str_field[j]='\0';
	printf("\nstr field --> %s ",str_field);
	i++;
	j=0;
	while((cBuffer[i] != ',') && (i<strlen(cBuffer)))
		str_sessiontype[j++]=cBuffer[i++];
	str_sessiontype[j]='\0';
	printf("\nstr sessiontype--> %s ",str_sessiontype);
	j=0;
	i++;
	while((cBuffer[i] != '\0') && (i<strlen(cBuffer)))
                        str_uid[j++] = cBuffer[i++];
	for(i=0;i<rec_index;i++){
		printf("\ninside for");
		if((strcmp(str_name,list[i].name) == 0) && (strcmp(str_type,list[i].type) == 0) && (strcmp(str_field,list[i].field) == 0)&& (strcmp(str_sessiontype,list[i].sessiontype) == 0) && (strcmp(str_uid,list[i].iUid)==0)){
 
			printf("\n matched name id =%s",list[i].name);
			printf("\n matched type id =%s",list[i].type);
			printf("\n matched uid --> %s",list[i].iUid);
			return(atoi(list[i].iSid));
		}
	}

	return 1;
/*luid=(atoi(ulist[rec_index-1].iUid));
if(rec_index > 0)
  return ++luid;
else
return ++uid;*/
}
