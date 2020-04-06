#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "cpfapi.h"
#define MAX 100
extern int iSid;
int svc_reg( char *cBuffer , int iUid ){
	FILE *fp;
	int i = 0,j = 0,k = 0,count=0;
	char cSvc_name[100],cSvc_type[100],cSvc_status[100];
	if(cBuffer!=NULL && cBuffer[0]!=" "){
		while(cBuffer[i] != ',')
			cSvc_name[i++] = cBuffer[i];
		cSvc_name[i]='\0';
		i++;
                while(cBuffer[i] != ',')
			cSvc_type[k++] = cBuffer[i++];
		cSvc_name[k]='\0';
		i++;
		while(cBuffer[i] != '\0')
			cSvc_status[j++] = cBuffer[i++];
		cSvc_status[j]='\0';
		if(strlen(cSvc_name)!=0){
			for(int i=0;cSvc_name[i]!='\0';i++){
				if(isalpha(cSvc_name[i]))
//||  (cSvc_name[i]==' ' && i!=0 && ++count && count <= 1))
					continue;
				//}
			}
	//else
		//printf("invalid service name");	
	count=0;
	//if(strlen(cSvc_type)!=0){
	for(int i=0;cSvc_type[i]!='\0';i++){
				if(isalpha(cSvc_type[i]) )
//||  (cSvc_type[i]==' ' && i!=0 && ++count && count <= 1))
					continue;
				}
	//}
	//else
		//printf("invalid service type");	
	count=0;
	//if(strlen(cSvc_type)!=0){
	for(int i=0;cSvc_status[i]!='\0';i++){
				if(isalpha(cSvc_status[i]))
//||  (cSvc_status[i]==' ' && i!=0 && ++count && count <= 1))
					continue;
				}
	//}
	//else
		//printf("invalid status");
	fp = fopen("service_table.csv","a+");
	if (fp == NULL){
		printf("Can't open a file");
		exit(0);
	}
	
	printf("%d %s %s %s %d\n",iUid,cSvc_name,cSvc_type,cSvc_status,iSid);
	fprintf(fp,"%d %s %s %s %d\n",iUid,cSvc_name,cSvc_type,cSvc_status,iSid);
	fclose(fp);
	memset(&cBuffer,0,sizeof(cBuffer));
	//printf("%d",iSid);
	return iSid;
}
}
}


