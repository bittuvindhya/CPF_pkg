#include <stdio.h> 
#include <string.h> 
#include<stdlib.h>
#include "cpfapi.h"
#include<fcntl.h>
#define MAX 2048

#define  SVC_LIST_DB    "/home/vindhya/pkg_3/service_reg_table.csv"
#define  SESSION_LIST_DB    "/home/vindhya/pkg_3/session_list_table.csv"

struct get_list slist[100];
struct session list[100];

char* svc_field(char* session_id) 
{ 
	char buff[1024],*cfield,cSid[5];
     	int count=0,last=0,i=0,sid=3000;
	cfield=(char*)malloc(MAX*sizeof(char));
	//cfield=(char*)malloc(MAX*sizeof(char));
	//cSid=(char*)malloc(MAX*sizeof(char));
	int rec_index=0;
	int bytes_read = 0;
	int fd1 = open(SESSION_LIST_DB, O_CREAT|O_RDWR|O_APPEND);    
	fprintf(stderr, "INFO: Reading service data..\n");
	while((bytes_read = read(fd1, (void *)&list[rec_index], sizeof(struct session))) != 0){  
                        rec_index++;
        }
	close(fd1);
	
	printf("READDDING DONE\n");
	for(i=0;i<rec_index;i++){
		printf("Session table : list[i].iSession_id %s",list[i].iSession_id);
		printf("Session table : list[i].iSid %s",list[i].iSid);
		if(strncmp(list[i].iSession_id,session_id,4) == 0){
			strcpy(cSid,list[i].iSid);
			printf("cSid =>%s\n",cSid);
		}
		else
			printf("INFO:session id not matched\n");
	}

	rec_index = 0;	
	bytes_read = 0;
	int fd = open(SVC_LIST_DB, O_CREAT|O_RDWR|O_APPEND);
	while((bytes_read = read(fd, (void *)&slist[rec_index], sizeof(struct get_list))) != 0){          	               
		rec_index++;
        }

	close(fd);
	for(i=0;i<rec_index;i++){
		if(strncmp(cSid,slist[i].iSid,4) == 0){
			strcpy(cfield,slist[i].field);
			printf("cfield=>%s\n",cfield);
		}
		else
			printf("INFO : service id not matced\n");
	}
	return cfield;
}

	
	
