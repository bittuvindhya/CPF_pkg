#include <stdio.h> 
#include <string.h> 
#include<stdlib.h>
#include "cpfapi.h"
#include<fcntl.h>

#define SUB_DB   "/home/vindhya/pkg_3/subscribe_table.csv"

struct  subscribe sub[100];

int sub_retrive() 
{ 
	char buff[1024],*str,*token;
     	int count=0,last=0,i=0,iSubid=6000;
	int fd = open(SUB_DB, O_CREAT|O_RDWR|O_APPEND);
        int bytes_read = 0;
	 int rec_index=0;

	while((bytes_read = read(fd, (void *)&sub[rec_index], sizeof(struct subscribe))) != 0){
                        rec_index++;
        }

 	for(i=0;i<rec_index;i++){
                        fprintf(stderr,"INFO: SERVICE DATA (%d)\n",i);
                        fprintf(stderr,"      -----> SERVICE ID    : (%s)\n",sub[i].iSid);
                        fprintf(stderr,"      -----> SERVICE NAME  : (%s)\n",sub[i].iUid);
                        fprintf(stderr,"      -----> SERVICE TYPE  : (%s)\n",sub[i].iSubid);
                       
 	}
 	if(rec_index > 0)
 		return(atoi(sub[rec_index-1].iSubid));
 	else 
	 	return iSubid;
}
/*void main()
{
int i;
i=uid_retrive();
printf("\ni=>%d",i);
}*/
