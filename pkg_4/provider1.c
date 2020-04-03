#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include <dirent.h>
#include <error.h>
#include <errno.h>
#include <regex.h>
#include<ctype.h>
#include<stdbool.h>
#include<pthread.h>
#include "cpfapi.h"
#include "validation1.h"
#include<dlfcn.h>
#define server_ip "127.0.0.1"
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
	char *pField=(char*)malloc(100*sizeof(char));
	char *psessiontype=(char*)malloc(100*sizeof(char));

        memset(pSvcName, 0, sizeof(pSvcName));
        memset(pSvcType, 0, sizeof(pSvcType));
        memset(pSvcStatus, 0, sizeof(pSvcStatus));
        memset(pUid, 0, sizeof(pUid));
        memset(pBuffer, 0, sizeof(pBuffer));
        memset(plugin_path, 0, sizeof(plugin_path));
	memset(pField, 0, sizeof(pField));
	memset(psessiontype, 0, sizeof(psessiontype));
	
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
		strcat(pBuffer," , ");
                        svc[i].getstatus=dlsym(svc[i].pHandle,"getstatus");
                        pSvcStatus=svc[i].getstatus();
                                if ( svc[i].getstatus== NULL) {
                                        fprintf(stderr, "ERROR: symbol not found..Skipping..\n");
                                        continue;
                                }
                        strcat(pBuffer,pSvcStatus);
			strcat(pBuffer,",");
                        svc[i].getfield=dlsym(svc[i].pHandle,"getfield");
                        pField=svc[i].getfield();
			//printf("field=>%s",pField);
                                if ( svc[i].getfield== NULL) {
                                        fprintf(stderr, "ERROR: symbol not found..Skipping..\n");
                                        continue;
                                }
			strcat(pBuffer,pField);
			strcat(pBuffer,",");
                        svc[i].getsessiontype=dlsym(svc[i].pHandle,"getsessiontype");
                        psessiontype=svc[i].getsessiontype();
			//printf("psessiontype=>%s",psessiontype);
                                if ( svc[i].getsessiontype== NULL) {
                                        fprintf(stderr, "ERROR: symbol not found..Skipping..\n");
                                        continue;
                                }
			strcat(pBuffer,psessiontype);
			strcat(pBuffer,",");
                        svc[i].getuid=dlsym(svc[i].pHandle,"getuid");
			pUid=svc[i].getuid();
			printf("\ngetuid is %s",pUid);
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
        pBuffer[strlen(pBuffer)]='\0';
        return pBuffer;
}

void *server_thread ( void *arg ){               //thread function

        int msg_len=0,i;
        int newsock_fd=(int)arg;
	int ibuffer=0,session_id=0;
        char *buffer1,buffer[MAX],*buf,buffer2[MAX],*str;
	buf=(char *)malloc(MAX*sizeof(char));
	ssid=(char*)malloc(2048*sizeof(char));

	if(buf == NULL){
		printf("\n error in memory allocation\n");
		return NULL;
	}

	memset(buffer, 0, sizeof(buffer));
	memset(buffer2, 0, sizeof(buffer2));
	strcpy(buffer, "..........welcome.........");
       
	buffer1=(char*)malloc(MAX*sizeof(char));
	msg_len=write(newsock_fd, buffer, MAX);
	printf("msg_len-->%d",msg_len);
	printf("\nINFO:inside server thread at provider side ");
 	
        while(1){
		memset(&buffer,0,sizeof(buffer));
		msg_len=read(newsock_fd,buffer,MAX);
		printf("\nbuffer received at server %s",buffer);

		if(msg_len<=0){
			break;
		}
			str=strtok(buffer,":");

			if(strncmp(str,"START_SESSION",13)==0) {
				ssid=strchr(buffer,":");
				printf("\nEnter your response ,if Ok to provide service enter");
				scanf("%s",buf);
			}
		
			else if(strncmp(str,"INPUT",5)==0){
				printf("\ncomparing INPUT success");
				buf=svc_provider(buffer,ssid);
			}
	
			else{
				printf("\nImproper input from subscriber ");
			}
			msg_len=write(newsock_fd, buf, MAX);
			/*//int request_validation(char *buf, req_type, req_input);
			//int return_code = request_validation(buf, req_type, req_input);

			int return_code = request_validation(buf, &req_type, req_input);
			if(return_code != 0){
				printf("The commannd is not correct");
				break;
			}
			else{
				if(req_type<T_START_SESSION){

					return_code=process_cpf_req(&req_type,req_input,resp_output);
				}
				else{
					return_code=process_provider_req(&req_type,req_input,resp_output);
				}				
			}
			strcpy(buffer1,resp_output);
			msg_len=write(newsock_fd, buffer1, MAX);
			printf("\n%d",msg_len);
		}*/
	}
	
	//close(newsock_fd);
}
int server()
{
        int sock_fd,newsock_fd,cliaddrlen,bind_check,lis_check;
        struct sockaddr_in servaddr,cliaddr;
        pthread_t serverThread;
        sock_fd=socket(AF_INET,SOCK_STREAM,0);

        if(sock_fd<0)
                printf("\nSocket not created");
       
        printf("\nSocket created");
        memset(&servaddr,0,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        servaddr.sin_port=htons(PORT_NO);
        bind_check=bind(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));

        if(bind_check<0)
		printf("\nSocket not binded");
        else
		printf("\nBinding");
        lis_check=listen(sock_fd,5);

        if(lis_check<0)
                printf("\nListening failed");
   	else
	        printf("\nlistening");

        while(1){
                printf("\nSERVER WAITING FOR NEW CONNECTION\n");
                cliaddrlen=sizeof(cliaddr);
                newsock_fd=accept(sock_fd,(struct sockaddr*)&cliaddr,&cliaddrlen);

                if(newsock_fd<0)
                        printf("\nClient not connected");
             	else
	                printf("CONNECTED TO CLIENT\n");
                pthread_create(&serverThread,NULL,&server_thread,(void *)newsock_fd);
        }
	return 0;
}



int client()
{

	int sock_fd=0,msg_len=0,value=0,uid=0,ibuffer=0;
	struct sockaddr_in servaddr;
	char *buff, buffer[MAX],buffer2[MAX];
	sock_fd=socket(AF_INET,SOCK_STREAM,0);
	buff=load();
	//strcpy(buffer2,buff);
	buff[strlen(buff)] = '\0';
	printf("\nbuff--->%s",buff);
	//value=reg_svc_validation1(buff);
	//printf("\n value=%d",value);
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(server_ip);
	servaddr.sin_port=htons(PORT);
	connect(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	memset(buffer, 0, sizeof(buffer));
	msg_len=recv(sock_fd,buffer,MAX,0);	
        printf("\n%s\n",buffer);
	memset(&buffer,0,sizeof(buffer));
	
	
	
	
	//if(value==1){
		write(sock_fd, buff,MAX);
	//}
	memset(&buff,0,sizeof(buff));
	msg_len=read(sock_fd,buffer,MAX);
	printf("%s\n",buffer);
	//close(sock_fd);
	server();
	return 0;
}


void main()
{
	client();
}
