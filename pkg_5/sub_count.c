#include <stdio.h> 
#include <string.h> 
#include<stdlib.h>
#include "validation.h"
#include<fcntl.h>

#define  SUB_COUNT_DB    "/home/vindhya/pkg_5/sub_count.csv"

struct sub_count count[3];

int subscriber_count() 
{ 
     	int count=0,i=0;
	printf("\n entered in sub_count");
	int fd = open(SUB_COUNT_DB, O_CREAT|O_RDWR|O_APPEND);
        int bytes_read = 0;
	int rec_index=0;

	while((bytes_read = read(fd, (void *)&count[rec_index], sizeof(struct sub_count))) != 0){
                        rec_index++;
        }
	
	for(i=0;i<rec_index;i++){
                        fprintf(stderr,"INFO: UID DATA (%d)\n",i);
                        fprintf(stderr,"      -----> UID    : (%s)\n",count[i]. iCount);
 	}
	if(rec_index < 3)
 		return count;
	else 
		return -1;
}

