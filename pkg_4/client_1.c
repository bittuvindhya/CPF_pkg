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

	int sock_fd=0,msg_len=0,val=0,uid=0,id = 0,ibuffer=0,i=0,j=0,len=0,check1 = 0;
	struct sockaddr_in servaddr;
	char buffer[max],*buffer2,buffer1[max],buff[5],*check;

	sock_fd=socket(AF_INET,SOCK_STREAM,0);
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(server_ip);
	servaddr.sin_port=htons(PORT);

	check1 = connect(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	if(check1 != 0){	
		printf("\nINFO: Connection not established\n");
		close(sock_fd);
		exit(0);
	}else{

		memset(buffer, 0, sizeof(buffer));

		msg_len=recv(sock_fd,buffer,max,0);	
        	printf("\n%s\n",buffer);

		while(1){
			memset(&buffer,0,sizeof(buffer));
			fgets(buffer,max,stdin);
			buffer[strlen(buffer)] = '\0';
			val = main_validation(buffer,uid);
			/*if(strncmp(buffer,"ifconfig", 8) == 0){
			strcpy(buffer1,buffer);
			buffer2 = ifconfig();
			printf("\nbuffer for service result %s",buffer2);
			strcpy(buffer,buffer2);
			}*/
			//printf("%d",val);
			if((val == 1)||(val == 10)){
				write(sock_fd, buffer, max);

				if (val == 10)
					break;
			
				memset(&buffer,0,sizeof(buffer));
				msg_len=read(sock_fd,buffer, max);
				printf("%s\n",buffer);
				/*if(strlen(buffer)<=5){
					ibuffer=atoi(buffer);
					if((ibuffer>=1001) && (ibuffer<=3000))
						uid=ibuffer;
					else if((ibuffer>=6001) && (ibuffer<=8000))
						uid=ibuffer-5000;
					id_validation(buffer);
				}
				else*/
					//strcpy(buffer1,buffer);
				
				id = atoi(buffer);	
				if(id<3000&&id>1000)
					uid = id;
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
	close(sock_fd);
	}
	return 0;
}

void main()
{
	client();
}








