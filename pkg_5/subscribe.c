#include<stdio.h>

#include<string.h>

#include<stdlib.h>

#include "cpfapi.h"

#include <errno.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#define MAX 2048

#define SUB_DB "/home/vindhya/pkg_5/subscribe_table.csv"

#define SVC_LIST_DB "/home/vindhya/pkg_5/service_reg_table.csv"

char* sub_subscribe(char *cBuffer){

char cUid[5],cSid[5],sid[5];

char *ptr = NULL;

int rec_index = 0,len = 4,ret=0;

int bytes_written = 0,bytes_read1 =0;

char *buf = (char*)malloc(MAX*sizeof(char));

struct subscribe sub;

struct subscribe sub1[100];

int i = 0,j = 0;

if(cBuffer == NULL){

fprintf(stderr,"No parameter received\n");

return NULL;

}

memset(&cUid,0,sizeof(cUid));

memset(&cSid,0,sizeof(cSid));

if((ptr = strchr(cBuffer,','))!=NULL){

strncpy(sub.iUid,cBuffer,ptr-cBuffer);

ptr++;

strcpy(sub.iSid,ptr);

}

/*printf("\n sid=%s,uid=%s",sub.iSid,sub.iUid);

int fd = open(SUB_DB,O_CREAT|O_RDWR|O_APPEND);

while((bytes_read1 = read(fd, (void *)&sub, sizeof(sub))) != 0){

rec_index++;

}

*/

int fd = open(SUB_DB,O_CREAT|O_RDWR|O_APPEND);

while((bytes_read1 = read(fd, (void *)&sub1[rec_index], sizeof(sub))) != 0){

rec_index++;

}

for(i= 0 ;i<rec_index;i++){

fprintf(stderr," -----> UID : (%s)\n",sub1[i].iUid);

fprintf(stderr," -----> SERVICE ID : (%s)\n",sub1[i].iSid);

}

if (fd <= 0){

printf("ERROR: Can't open a file: (%d), (%s)\n", errno, strerror(errno));

exit(0);

}

bytes_written = write(fd, (void *)&sub, sizeof(struct subscribe));

close(fd);

int fd1 = open(SVC_LIST_DB, O_CREAT|O_RDWR|O_APPEND);

int bytes_read = 0;

int index=0;

struct get_list list[100];

printf("\n exist sid");

while((bytes_read = read(fd1, (void *)&list[index], sizeof(struct get_list))) != 0){

index++;

}

int sssid=atoi(sub.iSid);

for(i=0;i<index;i++){

int ssid=atoi(list[i].iSid);

if(sssid==ssid){

ret++;

}

}

close(fd1);

if(ret==1)

strcpy(buf,"you are successfully subscribed");

else

strcpy(buf,"Invalid service ID,re-enter again");

return buf;

}

/*int exist_sid(char *sid_val){

char buff[1024],*str,*token;

int count=0,last=0,i=0,sid=3000;

int fd = open(SVC_LIST_DB, O_CREAT|O_RDWR|O_APPEND);

int bytes_read = 0;

int rec_index=0;

struct get_list list[100];

printf("\n exist sid");

while((bytes_read = read(fd, (void *)&list[rec_index], sizeof(struct get_list))) != 0){

rec_index++;

}

for(i=0;i<rec_index;i++){

if(strcmp(sid_val,list[i].iSid) == 0){

printf("\n compared----sid=%s,iSid=%s",sid,list[i].iSid);

fprintf(stderr," -----> SERVICE ID : (%s)\n",list[i].iSid);

return 1;

}

else

return 0;

}

}*/ 
