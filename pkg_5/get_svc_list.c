#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include"cpfapi.h"
#define  SVC_LIST_DB	"/home/mubin/project/original/service_reg_table.csv"

typedef enum {
	SVC_SID=0,
	SVC_NAME,
	SVC_TYPE,
	SVC_STATUS,
	SVC_FIELD,
	SVC_SESSIONTYPE,
	SVC_IUID
}SVC_FIELDS;

int count = 0;
struct get_list list[100];

char* get_svc_list(char *cBuffer){
	char *buff = NULL;
	char cUid[5],cCategory[12];
        int last = 0;
	
	cBuffer[strlen(cBuffer)-1] = '\0';
	if (cBuffer == NULL) {
		fprintf(stderr, "ERROR: get_svc_list - NULL parameter received\n");
		return NULL;
	}
	printf("\n~~~~~~~~~~~~~~~~\n");
	fprintf(stderr, "INFO: Creating or Opening service database\n");
        int fd = open(SVC_LIST_DB, O_CREAT|O_RDWR|O_APPEND);
        int bytes_read = 0;
	int i = 0,j = 0;
	char *p = NULL;

	fprintf(stderr, "INFO: Parsing inputs..\n");

	memset(cUid, 0, sizeof(cUid));
	memset(cCategory, 0, sizeof(cCategory));
	if ((p = strchr(cBuffer, ',')) != NULL){
		strncpy(cUid, cBuffer, p-cBuffer);
		p++;
		strcpy(cCategory, p);
	}
	
	fprintf(stderr, "INFO: LIST = (%s)..\n", cCategory);

	int rec_index=0;
	fprintf(stderr, "INFO: Reading service data..\n");
	while((bytes_read = read(fd, (void *)&list[rec_index], sizeof(struct get_list))) != 0){
                        rec_index++;
        }

	fprintf(stderr, "Number of service records in the file = (%d)\n",rec_index);
        close(fd);

	char *cBuffer1 = NULL;
	printf("INFO: Memory required for (%d) records = (%d)..\n", rec_index, (rec_index * sizeof(struct get_list)));
	cBuffer1=(char *)malloc(4000);

	if(strcmp(cCategory,"all") == 0){
		printf("INFO: Inside category = ALL..\n");
		memset(cBuffer1, 0, sizeof(cBuffer1));
		printf("INFO: Successfully Allocated  Memory..\n");

		if(cBuffer1 == NULL){
			printf("\n error in memory allocation\n");
			return NULL;
		}

		memset(cBuffer1, 0, ((rec_index+1) * sizeof(struct get_list)));
		strcpy(cBuffer1,"SID  NAME  TYPE  FIELD SESSIONTYPE UID\n");

		fprintf(stderr, "INFO: Parsing service record..\n");
		fflush(stderr);
		for(i=0;i<=rec_index;i++){
		/*	fprintf(stderr,"INFO: SERVICE DATA (%d)\n",i);
			fprintf(stderr,"      -----> SERVICE ID    : (%s)\n",list[i].iSid);
			fprintf(stderr,"      -----> SERVICE NAME  : (%s)\n",list[i].name);
			fprintf(stderr,"      -----> SERVICE TYPE  : (%s)\n",list[i].type);
			fprintf(stderr,"      -----> SERVICE STATUS: (%s)\n",list[i].status);
			fprintf(stderr,"      -----> SERVICE UID   : (%s)\n",list[i].iUid);*/
			j = 0;
			do{
		 		switch(j){
                                	case SVC_SID:
						strcat(cBuffer1," ");
                        			strcat(cBuffer1,list[i].iSid);
                                                break;
                                        case SVC_NAME:
						strcat(cBuffer1," ");
						strcat(cBuffer1,list[i].name);
                                                break;
                                        case SVC_TYPE:
						strcat(cBuffer1," ");
						strcat(cBuffer1,list[i].type);
                                                break;
                                        case SVC_STATUS:
                                                break;
					case SVC_FIELD:
                                                 strcat(cBuffer1," ");
                                                 strcat(cBuffer1,list[i].field);
                                                 break;
                                         case SVC_SESSIONTYPE:
                                                 strcat(cBuffer1," ");
                                                 strcat(cBuffer1,list[i].sessiontype);
                                                 break;
                                        case SVC_IUID:
						strcat(cBuffer1," ");
						strcat(cBuffer1,list[i].iUid);
						strcat(cBuffer1,"\n");
                                        default :
                                                break;
                                }
                                j++;
			}while(j <= 6);
		}
		printf("get_svc_list=>%s\n",cBuffer1);
		return(cBuffer1);
	} 
	else if(strncmp(cCategory,"all",3) == 0){
		strcpy(cBuffer1,"Please enter valid category");
	}
	else {
		fprintf(stderr, "INFO: Inside category != ALL..\n");
		memset(cBuffer1, 0, ((rec_index+1) * sizeof(struct get_list)));
		strcpy(cBuffer1,"SID  NAME  TYPE  FIELD SESSIONTYPE UID\n");
                for(i=0;i<rec_index;i++){
			if((strcmp(cCategory,list[i].iUid)==0) || (strcmp(cCategory,list[i].name)==0)){
						j = 0;
				fprintf(stderr,"INFO: Entering != ALL\n");
                        	do{
                                	switch(j){
                                        	case SVC_SID:
                                                	strcat(cBuffer1," ");
                                                	strcat(cBuffer1,list[i].iSid);
                                                	break;
                                        	case SVC_NAME:
                                                	strcat(cBuffer1," ");
	                                                strcat(cBuffer1,list[i].name);
	                                                break;
        	                                case SVC_TYPE:
                	                                strcat(cBuffer1," ");
                        	                        strcat(cBuffer1,list[i].type);
                                	                break;
                                        	case SVC_STATUS:
                                                	break;
						case SVC_FIELD:
                                                        strcat(cBuffer1," ");
                                                        strcat(cBuffer1,list[i].field);
                                                        break;
						case SVC_SESSIONTYPE:
                                                        strcat(cBuffer1," ");
                                                        strcat(cBuffer1,list[i].sessiontype);
                                                        break;
	                                        case SVC_IUID:
        	                                        strcat(cBuffer1," ");
                	                                strcat(cBuffer1,list[i].iUid);
							strcat(cBuffer1,"\n");
							break;
						default :
                                	                break;
	                               	}	
        	                        j++;
                	        }while(j <= 6);
			}
		}		
	}
	fprintf(stderr, "INFO: get_svc_list complete %s\n",cBuffer1);

	cBuffer1[strlen(cBuffer1)] = '\0';
        return(cBuffer1);
}

