#include <stdio.h> 
#include <string.h> 
#include<stdlib.h>
#include "cpfapi.h"
#include<fcntl.h>

#define  SESSION_LIST_DB    "/home/vindhya/pkg_5/session_list_table.csv"

struct session slist[100];

int sessionid_retrive() 
{ 
	char buff[1024],*str,*token;
     	int count=0,last=0,i=0,session_id=7000;
	printf("\n entered in sessionid_retrieve");
	int fd = open(SESSION_LIST_DB, O_CREAT|O_RDWR|O_APPEND);
        int bytes_read = 0;
	 int rec_index=0;

	while((bytes_read = read(fd, (void *)&slist[rec_index], sizeof(struct session))) != 0){
                        rec_index++;
        }
	
 for(i=0;i<rec_index;i++){
                        fprintf(stderr,"INFO: UID DATA (%d)\n",i);
                        fprintf(stderr,"      -----> SESSION_ID    : (%s)\n",slist[i].iSession_id);
                        fprintf(stderr,"      -----> SID: (%s)\n",slist[i].iSid);
                        fprintf(stderr,"      -----> UID   : (%s)\n",slist[i].iUid);
 }
 if(rec_index > 0)
 	return(atoi(slist[rec_index-1].iSession_id));
 else 
	 return session_id;
}

