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
#define  UID_LIST_DB    "/home/xyz/project/krithika/uid_list_table.csv"//change the path of csv file

int uid = 0;

typedef enum {
	IUID = 0,
	NAME,
	MAILID
}UID_FIELDS;

int uim( char *cBuffer){
	bool check=false;

	char buffer[5],*cSid;
	int fd = 0, len = 4, exist = 0;
	struct uid_list ulist;
	int i = 0,l=0;
	int count = 0,rv=0;
	char *str;
	int bytes_written = 0;

	printf("\ncbuffer in  uid %s",cBuffer);
	uid=uid_retrive(cBuffer);
	printf("\nuid retrived %d",uid);
	exist = uid_exist(cBuffer);
	printf("\nuid exist %d",exist);

	if(exist == 1){
		if(strlen(cBuffer) && cBuffer!=NULL && cBuffer[0]!=" "){
			str=strtok(cBuffer,",");
			do{
				if(i>1 && i<=2)
					str = strtok(NULL, ",");
				if(strlen(str)!=0){
					switch (i) {
						case IUID:
							getDecStr(buffer,len,uid);
							strcpy(ulist.iUid,buffer);
							break;
						case NAME:
							strcpy(ulist.name,str);
							break;
						case MAILID:
							strcpy(ulist.mailid,str);
							break;
						default :
							break;
					}
					i++;
				}
			}while(str != NULL && i <= 2 );



			printf("\nBefore writing into file %s %s %s ",ulist.iUid,ulist.name,ulist.mailid);

			fd = open(UID_LIST_DB, O_CREAT|O_RDWR|O_APPEND);
			if (fd <= 0){
				printf("ERROR: Can't open a file: (%d), (%s)\n", errno, strerror(errno));
				exit(0);
			}
		}

		bytes_written = write(fd, (void *)&ulist, sizeof(struct uid_list));
		close(fd);
		memset(&cBuffer,0,sizeof(cBuffer));
		return uid;
	}else{
                memset(&cBuffer,0,sizeof(cBuffer));
		return 1;
	}
}

