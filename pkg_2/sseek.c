#include <stdio.h> 
#include <string.h> 
#include<stdlib.h>
#include "cpfapi.h"
#include<fcntl.h>

#define  SVC_LIST_DB    "/home/vindhya/pkg_2/service_reg_table.csv"

struct get_list list[100];

int sid_retrive() 
{ 
	char buff[1024],*str,*token;
     	int count=0,last=0,i=0,sid=3000;
	int fd = open(SVC_LIST_DB, O_CREAT|O_RDWR|O_APPEND);
        int bytes_read = 0;
	int rec_index=0;

	while((bytes_read = read(fd, (void *)&list[rec_index], sizeof(struct get_list))) != 0){
                        rec_index++;
        }
 for(i=0;i<rec_index;i++){
                        fprintf(stderr,"INFO: SERVICE DATA (%d)\n",i);
                        fprintf(stderr,"      -----> SERVICE ID    : (%s)\n",list[i].iSid);
                        fprintf(stderr,"      -----> SERVICE NAME  : (%s)\n",list[i].name);
                        fprintf(stderr,"      -----> SERVICE TYPE  : (%s)\n",list[i].type);
                        fprintf(stderr,"      -----> SERVICE STATUS: (%s)\n",list[i].status);
  			fprintf(stderr,"      -----> SERVICE FIELD  : (%s)\n",list[i].field);
			fprintf(stderr,"      -----> SERVICE SESSIONTYPE  : (%s)\n",list[i].sessiontype);
  			fprintf(stderr,"      -----> SERVICE UID   : (%s)\n",list[i].iUid);
 }
 if(rec_index > 0)
 	return(atoi(list[rec_index-1].iSid));
 else 
	 return sid;
}

/*void main()
{
int i;
i=uid_retrive();
printf("\ni=>%d",i);
}*/
