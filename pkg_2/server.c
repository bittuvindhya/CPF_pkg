#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>i
#include<sys/socket.h>
#include<string.h>
#include "cpfapi.h"
#define MAX 2048

void *client_thread ( void *arg )               //thread function
{
        int msg_len=0,i;
        int newsock_fd=(int)arg;
	int ibuffer=0,uid=0;
        char *buffer1,buffer[MAX],*buf,buffer2[MAX];
	buf=(char *)malloc(MAX*sizeof(char));

	if(buf == NULL){
		printf("\n error in memory allocation\n");
		return NULL;
	}

	memset(buffer, 0, sizeof(buffer));
	memset(buffer2, 0, sizeof(buffer2));
	strcpy(buffer, "..........welcome.........");
        
	buffer1=(char*)malloc(MAX*sizeof(char));
	write(newsock_fd, buffer, sizeof(buffer));
 
        while(1){
		memset(&buffer,0,sizeof(buffer));
		msg_len=read(newsock_fd,buffer,MAX);
		printf("\nbuffer received at server %s",buffer);
		if(msg_len<=0){
			break;
		}
		else{
			i=strlen(buffer);
			buffer[i]='\0';
			strcpy(buf,buffer);
			buf[strlen(buf)]='\0';
			memset(buffer1,0,sizeof(buffer1));
			buffer1=User_Validation(buf);
			buffer1[strlen(buffer1)] = '\0';
			if(strlen(buffer1)<=5){
                                ibuffer=atoi(buffer1);
                                if((ibuffer>=1001) && (ibuffer<=3000))
                                        uid=ibuffer;
                               /* else if((ibuffer>=6001) && (ibuffer<7000))
                                        uid=ibuffer-5000;*/
                                strcpy(buffer2,id_validation(buffer1));
				write(newsock_fd,buffer2,MAX);
                        }else{

	        	msg_len=write(newsock_fd, buffer1, MAX);
			printf("\n%d",msg_len);
			}
		}
	}
	close(newsock_fd);
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
        servaddr.sin_port=htons(PORT);
        bind_check=bind(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));

        if(bind_check<0)
		printf("\nSocket not binded");
       
        printf("\nBinding");
        lis_check=listen(sock_fd,5);

        if(lis_check<0)
                printf("\nListening failed");
   
        printf("\nlistening");

        while(1){
                printf("\nSERVER WAITING FOR NEW CONNECTION\n");
                cliaddrlen=sizeof(cliaddr);
                newsock_fd=accept(sock_fd,(struct sockaddr*)&cliaddr,&cliaddrlen);

                if(newsock_fd<0)
                        printf("\nClient not connected");
             
                printf("CONNECTED TO CLIENT\n");
                pthread_create(&serverThread,NULL,&client_thread,(void *)newsock_fd);
        }
return 0;
}


void main(){

	server();
}

