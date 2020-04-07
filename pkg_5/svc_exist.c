#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "cpfapi.h"
#include<fcntl.h>

#define  SVC_LIST_DB    "/home/vindhya/pkg_5/service_reg_table.csv"

struct get_list list[100];

int service_exist(char *cBuffer){
	char buff[1024],*str,*token;
      	int count=0,lsid=0,i=0,sid=3000,j = 0;
	printf("cbuffer  --> %s",cBuffer);
	printf("\n entered in service_exist");
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
                        fprintf(stderr,"      -----> MAILID  : (%s)\n",list[i].status);
 	 }
	i=0;
	while(cBuffer[i] != ',' && (i<strlen(cBuffer)))
		str[j++]=cBuffer[i++];
	str[j]='\0';
	printf("str name --> %s ",str);
	i++;
	j=0;
	for(i=0;i<rec_index;i++){
		if((strncmp(str,list[i].name,strlen(list[i].name)) == 0)){
			printf("\n matched name id =%s",list[i].name);
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
