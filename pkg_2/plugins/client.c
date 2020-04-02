#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include <regex.h>
#include<ctype.h>
#include<stdbool.h>
#define PORT 2021
#define server_ip "127.0.0.1"
#define max 255

int client()
{

	int sock_fd=0,msg_len=0,val=0;
	struct sockaddr_in servaddr;
	char buffer[max];
	//,*buffer1;
	//buffer1=(char*)malloc(4*sizeof(char));
	sock_fd=socket(AF_INET,SOCK_STREAM,0);
        printf("\nSocket created");
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(server_ip);
	servaddr.sin_port=htons(PORT);
	connect(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	while(1){
		memset(&buffer,0,sizeof(buffer));
		printf("enter \n");
		fgets(buffer,max,stdin);
		buffer[strlen(buffer)]='\0';
		if(buffer[0]=='!'){
			break;
		}
		else{
			send(sock_fd,buffer,max,0);
			memset(&buffer,0,sizeof(buffer));
			msg_len=recv(sock_fd,buffer,max,0);
			printf("buffer=>%s",buffer);
		}
	}	
	close(sock_fd);
	return 0;
}
void main()
{
	client();
}
