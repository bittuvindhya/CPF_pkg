#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include <regex.h>
#include<ctype.h>
#include<stdbool.h>
#include "validation.h"
#define server_ip "127.0.0.1"
#define max 2048

int client()
{

	int sock_fd=0,msg_len=0,val=0,uid=0,ibuffer=0,i=0,j=0,len=0;
	struct sockaddr_in servaddr;
	char buffer[max],buffer2[max],buffer1[max],buff[5],*check;
	sock_fd=socket(AF_INET,SOCK_STREAM,0);
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(server_ip);
	servaddr.sin_port=htons(PORT);
	connect(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	memset(buffer, 0, sizeof(buffer));
	msg_len=recv(sock_fd,buffer,max,0);	
        printf("\n%s\n",buffer);
	while(1){
		memset(&buffer,0,sizeof(buffer));
		fgets(buffer,max,stdin);
		buffer[strlen(buffer)] = '\0';
		val=main_validation(buffer,uid);

		if(val==1){

			write(sock_fd, buffer, max);
			memset(&buffer,0,sizeof(buffer));
			msg_len=read(sock_fd,buffer, max);

			/*if(strlen(buffer)<=5){
				ibuffer=atoi(buffer);
				if((ibuffer>=1001) && (ibuffer<=3000))
					uid=ibuffer;
				else if((ibuffer>=6001) && (ibuffer<=8000))
					uid=ibuffer-5000;
				id_validation(buffer);
			}
			else*/{
				//strcpy(buffer1,buffer);
				printf("%s\n",buffer);
				check=strstr(buffer,"your uid is ");
				if(check != NULL){
					len=strlen(buffer);
					for(i=len-4;i<len;i++){
						buff[j++]=buffer[i];
					}
					uid=atoi(buff);
				}
			}
		}
	}
	close(sock_fd);
	return 0;
}
void main()
{
	client();
}
