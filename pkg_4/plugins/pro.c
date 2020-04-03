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

#define PORT 2021
#define MAX 2048

#define PLUGIN_DIR  "plugins"

int so_count=0;
struct service svc[100];
void *handle[100];
void load(){
	char  plugin_path[255];
	char  file_path[1024];
	DIR*  pPluginsDir = NULL;
	struct dirent *pDirEntry = NULL;
	char *pSvcName=(char*)malloc(MAX*sizeof(char));
	char *pSvcType=(char*)malloc(MAX*sizeof(char));
	char *pSvcStatus=(char*)malloc(MAX*sizeof(char));
	char *pUid=(char*)malloc(MAX*sizeof(char));
	char *pBuffer=(char*)malloc(MAX*sizeof(char));
	

	memset(pSvcName, 0, sizeof(pSvcName));
	memset(pSvcType, 0, sizeof(pSvcType));
	memset(pSvcStatus, 0, sizeof(pSvcStatus));
	memset(pUid, 0, sizeof(pUid));
	memset(pBuffer, 0, sizeof(pBuffer));
	memset(plugin_path, 0, sizeof(plugin_path));

	printf("Path : (%s)\n", plugin_path);
	getcwd(plugin_path, sizeof(plugin_path));
	printf("Path : (%s)\n", plugin_path);

	strcat(plugin_path, "/");
	printf("Path : (%s)\n", plugin_path);
	
	strcat(plugin_path, PLUGIN_DIR);
	printf("Path : (%s)\n", plugin_path);

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
			so_count++;			
			continue;
		}
		printf("File : (%s)\n", pDirEntry->d_name);
		strcpy(file_path, plugin_path);
		strcat(file_path, "/");
		strcat(file_path, pDirEntry->d_name);

		printf("Loading plugin : (%s)\n", file_path);

        	//handle[0]=dlopen("/home/rupa/libfirst.so",RTLD_LAZY);
        	//handle[1]=dlopen("/home/rupa/libsecond.so",RTLD_LAZY);
        	pHandle=dlopen(file_path,RTLD_LAZY);

        	//if(!handle[0] || !handle[1]){
        	if(!pHandle){
                	fputs(dlerror(),stderr);
			closedir(pPluginsDir);
                	exit(0);
        	}

		printf("Finding symbol : (reg)\n");
		strcpy(pBuffer,"REG_SVC:");
        	//dfunc=dlsym(handle[0],"reg");
		for(i=0;i<so_count;i++){
        		svc[i].getname=dlsym(svc[i].pHandle,"getname");
			pSvcName=svc[i].getname();
			if ( svc[i].getname== NULL) {
				fprintf(stderr, "ERROR: symbol not found..Skipping..\n");
				continue;
			}
		}
		strcat(pBuffer,pSvcName);
		strcat(pBuffer," , ");
		for(i=0;i<so_count;i++){
        		svc[i++].gettype=dlsym(svc[i].pHandle,"gettype");
			pSvcType=svc[i].gettype();
			if ( svc[i].gettype== NULL) {
				fprintf(stderr, "ERROR: symbol not found..Skipping..\n");
				continue;
			}
		}
		strcat(pBuffer,pSvcType);
		strcat(pBuffer," , ");
		for(i=0;i<so_count;i++){
        		svc[i++].getstatus=dlsym(svc[i].pHandle,"getstatus");
			pSvcStatus=svc[i].getstatus();
			if ( svc[i].getstatus== NULL) {
				fprintf(stderr, "ERROR: symbol not found..Skipping..\n");
				continue;
			}
		}
		strcat(pBuffer,pSvcStatus);
		strcat(pBuffer," , ");
		for(i=0;i<so_count;i++){
        		svc[i++].getuid=dlsym(svc[i].pHandle,"getstatus");
			pUid=svc[i].getuid();
			if ( svc[i].getuid== NULL) {
				fprintf(stderr, "ERROR: symbol not found..Skipping..\n");
				continue;
			}
		}
		strcat(pBuffer,pUid);
		
		printf("pBuffer = > %s\n",pBuffer);
        	handle[i++] = pHandle;
	}
	printf("INFO: closing directory..\n");
	closedir(pPluginsDir);
	return pBuffer;
	
}

/*char* getname(){

        char* (*dfunc1)();
	char *str=(char*)malloc(MAX*sizeof(char));
	char *str1=(char*)malloc(MAX*sizeof(char));
        
	dfunc1=dlsym(handle[0],"getname");
        str=dfunc1();

        dfunc1=dlsym(handle[1],"getname");
        str1=dfunc1();

        strcat(str," , ");
        strcat(str,str1);
	return str;
}*/
int client(){

	int sock_fd=0,msg_len=0,val=0;
	struct sockaddr_in servaddr;
	char buffer[MAX];
	//,*buffer1;
	//buffer1=(char*)malloc(4*sizeof(char));
	sock_fd=socket(AF_INET,SOCK_STREAM,0);
        printf("\nSocket created");
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(server_ip);
	servaddr.sin_port=htons(PORT);
	connect(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	msg_len=recv(sock_fd,buffer,MAX,0);
	printf("buffer=>%s",buffer);
	memset(&buffer,0,sizeof(buffer));
	buffer=load();
	while(1){
		buffer[strlen(buffer)]='\0';
		send(sock_fd,buffer,MAX,0);
		memset(&buffer,0,sizeof(buffer));
		msg_len=recv(sock_fd,buffer,MAX,0);
		printf("buffer=>%s",buffer);
	}	
	close(sock_fd);
	return 0;
}
void main()
{
	client();
}
/*
void *client_thread(int socket_addr){

	int n,newsockfd;
	newsockfd=socket_addr;
	char *msg1,msg2[MAX];
	count++;

	while(1){
		n=recv(newsockfd,msg2,MAX,0);
		if(n==0){
			break;
		}
		else{
			msg2[n]='\0';
			if((strcmp(msg2,"list")) == 0){
				msg1=getname();
				send(newsockfd,msg1,MAX,0);
			}
		}
	}
	close(newsockfd);
}

int main(){

	int sockfd,newsockfd,client_addrlen,n;
	pthread_t tid;

	struct sockaddr_in server_addr,client_addr;

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(PORT);
	bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	listen(sockfd,5);
	load();	
	while(1){
		printf("\nSERVER IS WAITING FOR THE CLIENT CONNECTION...\n");
		client_addrlen=sizeof(client_addr);
		newsockfd=accept(sockfd,(struct sockaddr*)&client_addr,&client_addrlen);
		printf("CONNECTION ESTABLISHED\n");
		pthread_create(&tid,NULL,&client_thread,newsockfd);
	}
	return 0;
}
*/


