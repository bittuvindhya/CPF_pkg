#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include <dirent.h>
#include<fcntl.h>
#include <error.h>
#include <errno.h>
#include <regex.h>
#include<ctype.h>
#include<stdbool.h>
#include "cpfapi.h"
#include<dlfcn.h>
#define server_ip "127.0.0.1"
#define MAX 2048
#define  SESSION_LIST_DB	"/home/vindhya/pkg_5/session_list_table.csv"
#define  SVC_LIST_DB    "/home/vindhya/pkg_5/service_reg_table.csv"
#define PLUGIN_DIR  "./plugins"
#define MAX 2048

struct service svc[100];
struct session list[100];
struct get_list slist[100];

void *handle[100];

char *svc_provider(char *cBuffer,char *session_id){

        char  plugin_path[255];
        char  file_path[1024];
        int j = 0,bytes_read=0;
	int i= 0;
	int so_count=0;

        DIR*  pPluginsDir = NULL;
        struct dirent *pDirEntry = NULL;
        char *pUid=(char*)malloc(MAX*sizeof(char));
	char *cSid=(char*)malloc(MAX*sizeof(char));
	char *cUid=(char*)malloc(MAX*sizeof(char));
	char *uid=(char*)malloc(MAX*sizeof(char));

        char* pBuffer=(char*)malloc(MAX*sizeof(char));
	memset(pUid, 0, sizeof(pUid));
        memset(pBuffer, 0, sizeof(pBuffer));
		
	int fd = open(SESSION_LIST_DB, O_CREAT|O_RDWR|O_APPEND);    
	int rec_index=0;
	fprintf(stderr, "INFO: Reading service data..\n");
	while((bytes_read = read(fd, (void *)&list[rec_index], sizeof(struct session))) != 0){  
                        rec_index++;
        }
	close(fd);
	for(i=0;i<rec_index;i++){
		if(strncmp(list[i].iSession_id,session_id,4) == 0)
			strcpy(cSid,list[i].iSid);
		else
			printf("\n session id not matched");
	}
	printf("\n cSid=%s",cSid);
	
	fd = open(SVC_LIST_DB, O_CREAT|O_RDWR|O_APPEND);
	rec_index = 0;	
	while((bytes_read = read(fd, (void *)&slist[rec_index], sizeof(struct get_list))) != 0){          	               
		rec_index++;
        }
	close(fd);
	for(i=0;i<rec_index;i++){
		printf("\n slist[i].iSid=%s",slist[i].iSid);
		if(strncmp(cSid,slist[i].iSid,4) == 0)
			strcpy(cUid,slist[i].iUid);
		else
			printf("\n SID not matched");
	}
	printf("\n cUid=%s",cUid);
        printf("libparser2\n");
        printf("Path- : (%s)\n", plugin_path);
        getcwd(plugin_path, sizeof(plugin_path));
        printf("Path-- : (%s)\n", plugin_path);

        strcat(plugin_path, "/");
	printf("Path--- : (%s)\n", plugin_path);

        strcat(plugin_path, PLUGIN_DIR);
        printf("Path---- : (%s)\n", plugin_path);

        pPluginsDir = opendir(plugin_path);

        if (pPluginsDir == NULL) {
                switch (errno) {
                        case ENOENT:
                                fprintf(stderr, "ERROR: opendir failed: (%s) does not exists\n", pPluginsDir);
                                break;
                        case EACCES:
                                fprintf(stderr, "ERROR: opendir failed: (%s) cannot be opened\n", pPluginsDir);
                                break;
                        default:
                                fprintf(stderr, "ERROR: opendir failed: (%d)\n", errno);
                }
                return NULL;
        }

        while ((pDirEntry = readdir(pPluginsDir)) != NULL){
	 memset(file_path, 0, sizeof(file_path));
                if (strstr(pDirEntry->d_name, ".so") == NULL){
                        continue;
                }
                else
                        so_count++;
                printf("File : (%s)\n", pDirEntry->d_name);
                strcpy(file_path, plugin_path);
                strcat(file_path, "/");
                strcat(file_path, pDirEntry->d_name);

                printf("Loading plugin : (%s)\n", file_path);

                for(i=0;i<so_count;i++){
                        svc[i].pHandle=dlopen(file_path,RTLD_LAZY);
                        if(!svc[i].pHandle){
                                fputs(dlerror(),stderr);
                                closedir(pPluginsDir);
                                exit(0);
                        }

                        printf("Finding symbol SVC_PROVIDER : (reg)\n");
                        svc[i].getuid=dlsym(svc[i].pHandle,"getuid");
			uid=svc[i].getuid();
			printf("SVC_PRO uid => %s\n",uid);
			printf("SVC_PRO cUid => %s\n",cUid);

			if(strncmp(cUid,uid,4) == 0){
				svc[i].perform=dlsym(svc[i].pHandle,"perform");
		 		pBuffer=svc[i].perform(cBuffer);
				printf("SVC_PROVIDER pBuffer = > %s\n",pBuffer);
			}
			
			else
				printf("INFO : UID not matched\n");
			handle[j++] = svc[i].pHandle;
       		 }
	}
        printf("INFO: closing directory..\n");
        closedir(pPluginsDir);
        pBuffer[strlen(pBuffer)]='\0';
        return pBuffer;
}



