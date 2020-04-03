#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<dlfcn.h>
#include<string.h>
#include <dirent.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include "cpfapi.h"
#define server_ip "127.0.0.1"
#define PORT 2021
#define MAX 2048
#define PLUGIN_DIR  "./plugins"

int so_count=0;
struct service svc[100];
void *handle[100];

char* load(){
	char  plugin_path[255];
	char  file_path[1024];
	int j = 0;
	DIR*  pPluginsDir = NULL;
	struct dirent *pDirEntry = NULL;
	char *pSvcName=(char*)malloc(100*sizeof(char));
	char *pSvcType=(char*)malloc(100*sizeof(char));
	char *pSvcStatus=(char*)malloc(100*sizeof(char));
	char *pUid=(char*)malloc(100*sizeof(char));
	char* pBuffer=(char*)malloc(MAX*sizeof(char));

	memset(pSvcName, 0, sizeof(pSvcName));
	memset(pSvcType, 0, sizeof(pSvcType));
	memset(pSvcStatus, 0, sizeof(pSvcStatus));
	memset(pUid, 0, sizeof(pUid));
	memset(pBuffer, 0, sizeof(pBuffer));
	memset(plugin_path, 0, sizeof(plugin_path));

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
		return;
	}

	int i= 0;

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
		printf("so_count---->%d\n",so_count);


		//char* pBuffer=(char*)malloc(MAX*sizeof(char));
		for(i=0;i<so_count;i++){
        		svc[i].pHandle=dlopen(file_path,RTLD_LAZY);
        		if(!svc[i].pHandle){
                		fputs(dlerror(),stderr);
				closedir(pPluginsDir);
                		exit(0);
        		}

			printf("Finding symbol : (reg)\n");
			strcpy(pBuffer,"REG_SVC:");
			svc[i].getname=dlsym(svc[i].pHandle,"getname");
			pSvcName=svc[i].getname();
			if ( svc[i].getname== NULL) {
				fprintf(stderr, "ERROR: symbol not found..Skipping..\n");
				continue;
			}
			strcat(pBuffer,pSvcName);
			strcat(pBuffer,",");
        		svc[i].gettype=dlsym(svc[i].pHandle,"gettype");
			pSvcType=svc[i].gettype();
				if ( svc[i].gettype== NULL) {
					fprintf(stderr, "ERROR: symbol not found..Skipping..\n");
					continue;
				}
			strcat(pBuffer,pSvcType);
			strcat(pBuffer,",");
        		svc[i].getstatus=dlsym(svc[i].pHandle,"getstatus");
			pSvcStatus=svc[i].getstatus();
				if ( svc[i].getstatus== NULL) {
					fprintf(stderr, "ERROR: symbol not found..Skipping..\n");
					continue;
				}
			strcat(pBuffer,pSvcStatus);
			strcat(pBuffer,",");
        		svc[i].getuid=dlsym(svc[i].pHandle,"getuid");
			pUid=svc[i].getuid();
				if ( svc[i].getuid== NULL) {
					fprintf(stderr, "ERROR: symbol not found..Skipping..\n");
					continue;
				}
			strcat(pBuffer,pUid);
			printf("pBuffer = > %s\n",pBuffer);

        		handle[j++] = svc[i].pHandle;
		}
	}
	printf("INFO: closing directory..\n");
	closedir(pPluginsDir);
	printf("i---->%d\n",i);
	pBuffer[strlen(pBuffer)]='\0';
	return pBuffer;
	
	
}

int client(){

	int sock_fd=0,msg_len=0,val=0;
	struct sockaddr_in servaddr;
	char *buffer,buff[MAX],buffer1[MAX];
	int n = 0;

	sock_fd=socket(AF_INET,SOCK_STREAM,0);
        printf("\nSocket created");
	buffer=load();
	strcpy(buff,buffer);
	printf("\nstrcpy buffer %s",buff);
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(server_ip);
	servaddr.sin_port=htons(PORT);
	connect(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	printf("\nsocket connected");
	memset(&buffer1,0,sizeof(buffer1));
        msg_len=read(sock_fd,buffer1,MAX);
	printf("\nme--> %d",msg_len);
	printf("%s",buffer1);
	buff[strlen(buff)]='\0';
	msg_len=write(sock_fd,buff,MAX);
	printf("\nmessage %d",msg_len);
	memset(&buffer1,0,sizeof(buffer1));
	memset(&buff,0,sizeof(buff));
	msg_len=read(sock_fd,buff,MAX);
	printf("\nmessage_length--->%d",msg_len);
	printf("\nbuffer=>%s",buff);
	close(sock_fd);
	return 0;
}

void main(){
	client();
}


