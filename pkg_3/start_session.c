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
#define  SESSION_LIST_DB    "/home/vindhya/pkg_3/session_list_table.csv"

int session_id = 0;

typedef enum {
        SESSION_ID=0,
        IUID,
	ISID
}SESSION_FIELDS;

int generate_session_id( char *cBuffer){
	bool check=false;

	char buffer[5],*cSid;
	int fd = 0, len = 4;
	struct session slist;
	int i = 0,l=0;
	int count = 0,rv=0;
	char *str;
	int bytes_written = 0;
	
	printf("\ncbuffer in session id %s",cBuffer);
	session_id=sessionid_retrive();
	printf("\nsession id retrived %d",session_id);
	++session_id;

	
	if(strlen(cBuffer) && cBuffer!=NULL && cBuffer[0]!=" "){
		str=strtok(cBuffer,",");
		do
		{	
			if(i>1 && i<=2)
				str = strtok(NULL, ",");
			if(strlen(str)!=0){
				switch (i) {
					case SESSION_ID:
						getDecStr(buffer,len,session_id);
						strcpy(slist.iSession_id,buffer);
						break;
					case IUID:
						strcpy(slist.iUid,str);
						break;
					case ISID:
						strcpy(slist.iSid,str);
						break;
					default :
						break;
				}
				i++;
			}
		}while(str != NULL && i <= 2 );

		printf("\nBefore writing into session file %s %s %s ",slist.iSession_id,slist.iUid,slist.iSid);

		fd = open(SESSION_LIST_DB, O_CREAT|O_RDWR|O_APPEND);
		if (fd <= 0){
			printf("ERROR: Can't open a file: (%d), (%s)\n", errno, strerror(errno));
			exit(0);
		}
		
		bytes_written = write(fd, (void *)&slist, sizeof(struct session));
		close(fd);

		}
		memset(&cBuffer,0,sizeof(cBuffer));
		return session_id;
}

