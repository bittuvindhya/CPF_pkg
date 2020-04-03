#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include "cpfapi.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX 100
#define  SVC_LIST_DB    "/home/vindhya/pkg_4/service_reg_table.csv"

int iSid;
iSid=3000;

typedef enum {
        SVC_SID=0,
        SVC_NAME,
        SVC_TYPE,
        SVC_STATUS,
	SVC_FIELD,
	SVC_SESSIONTYPE,
        SVC_IUID
}SVC_FIELDS;

int svc_reg( char *cBuffer){
	bool check=false;

	char buffer[5],*cSid;
	int fd = 0, len = 4;
	struct get_list list;
	int i = 0,l=0,svc_exist_check= 0;
	int count = 0,rv=0;
	char *str;
	int bytes_written = 0;
	
	iSid=sid_retrive();
	printf("\nsid retrived %d",iSid);
	svc_exist_check = service_exist(cBuffer);

	if(svc_exist_check == 1){
		if(strlen(cBuffer) && cBuffer!=NULL && cBuffer[0]!=" "){
			str=strtok(cBuffer,",");
			do
			{	
				if(i>1 && i<=6)
					str = strtok(NULL, ",");
				
				if(strlen(str)!=0){
					switch (i) {
						case SVC_SID:
							getDecStr(buffer,len,iSid);
							strcpy(list.iSid,buffer);
							break;
						case SVC_NAME:
							strcpy(list.name,str);
							break;
						case SVC_TYPE:
							strcpy(list.type,str);
							break;
						case SVC_STATUS:
							strcpy(list.status,str);
							break;
						case SVC_FIELD:
                                               		strcpy(list.field,str);
                                               		break;
						case SVC_SESSIONTYPE:
                                                	strcpy(list.sessiontype,str);
                                                	break;
						case SVC_IUID:
							strcpy(list.iUid,str);
							break;
						default :
							break;
					}
					i++;
				}
			}while(str != NULL && i <= 6 );

			printf("\nBefore writing into file %s %s %s %s %s %s %s",list.iSid,list.name,list.type,list.status,list.field,list.sessiontype,list.iUid);
	
		fd = open(SVC_LIST_DB, O_CREAT|O_RDWR|O_APPEND);
			if (fd <= 0){
				printf("ERROR: Can't open a file: (%d), (%s)\n", errno, strerror(errno));
				exit(0);
			}
		}
		bytes_written = write(fd, (void *)&list, sizeof(struct get_list));
		close(fd);
		memset(&cBuffer,0,sizeof(cBuffer));
		return iSid;
	}
	else{
		memset(&cBuffer,0,sizeof(cBuffer));
		return 1;
	}
}

