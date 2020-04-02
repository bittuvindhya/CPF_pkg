#include <stdio.h> 
#include <string.h> 
#include<stdlib.h>
#include "cpfapi.h"
#include<fcntl.h>

#define  UID_LIST_DB    "/home/vindhya/pkg_2/uid_list_table.csv"

struct uid_list ulist[100];

int exuid_retrive(char *mailid) 
{ 
	char buff[1024],*str,*token;
     	int count=0,last=0,i=0,uid=1000;
	printf("\n entered in uid_retrieve");
	int fd = open(UID_LIST_DB, O_CREAT|O_RDWR|O_APPEND);
        int bytes_read = 0;
	 int rec_index=0;
	
	while((bytes_read = read(fd, (void *)&ulist[rec_index], sizeof(struct uid_list))) != 0){
                        rec_index++;
        }
	
	for(i=0;i<rec_index;i++){
                        fprintf(stderr,"INFO: UID DATA (%d)\n",i);
                        fprintf(stderr,"      -----> UID    : (%s)\n",ulist[i].iUid);
                        fprintf(stderr,"      -----> NAME: (%s)\n",ulist[i].name);
                        fprintf(stderr,"      -----> MAILID   : (%s)\n",ulist[i].mailid);
 	}
	for(i=0;i<rec_index;i++){
		if((strcmp(mailid,ulist[i].mailid))==0)
			return (atoi(ulist[i].iUid)+5000);
	}
	if(rec_index > 0)
 		return(atoi(ulist[rec_index-1].iUid));
	else 
		return uid;
}

