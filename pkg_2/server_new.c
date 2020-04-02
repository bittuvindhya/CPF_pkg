#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include "cpfapi.h"
#define MAX 2048
#define CONNECTION_LIMIT 5

int client_limit = 0;


void *client_thread ( void *arg ){               //thread function

        int msg_len=0,i;
        int newsock_fd=(int)arg;
	int ibuffer=0,uid=0;
        char buffer1[MAX],buffer[MAX],*str;

	memset(buffer, 0, sizeof(buffer));
	memset(buffer1, 0, sizeof(buffer1));

	strcpy(buffer, "..........welcome.........");
        write(newsock_fd, buffer, sizeof(buffer));
 
        while(1){
		memset(&buffer,0,sizeof(buffer));
		msg_len=read(newsock_fd,buffer,MAX);
		buffer[strlen(buffer)] = '\0';
		printf("\nbuffer received at server %s",buffer);
		if(msg_len<=0){
			break;
		}else{
			if(strncmp(buffer,"QUIT",4) == 0){
			client_limit--;
			break;
			}
			//int request_validation(char *buf, req_type, req_input);
			//int return_code = request_validation(buf, req_type, req_input);
			str =(char*)malloc(MAX*sizeof(char));
			printf("\nbuffer received at server %s",buffer);
			strcpy(str,buffer);
			printf("\nstr received at server %s",str);

			req_input =(char*)malloc(MAX*sizeof(char));
			memset(req_input,0,sizeof(req_input));
			int return_code = 0;
			return_code = request_validation(str, &req_type, req_input);
			printf("return_code =>%d",return_code);
			printf("return_code =>%s",req_input);

			if(return_code != 0){
				printf("The commannd is not correct");
				break;
			}else{
				if(req_type<T_START_SESSION){
					return_code=process_cpf_req(&req_type,req_input,resp_output);
				}else{
					return_code=process_provider_req(&req_type,req_input,resp_output);
				}
			}

			printf("\n resp output=%s buffer1=%s",resp_output,buffer1);
			memset(&buffer1,0,sizeof(buffer1));

			if(return_code == 1){
				strcpy(buffer1,"Existing user,your uid is ");
				strcat(buffer1,resp_output);
			}else{
				strncpy(buffer1,resp_output,strlen(resp_output));
			}
			msg_len=write(newsock_fd, buffer1, MAX);
			printf("\n%d",msg_len);
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
	else      
       		printf("\nSocket created");

        memset(&servaddr,0,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        servaddr.sin_port=htons(PORT);
        bind_check=bind(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));

        if(bind_check < 0){
		printf("\nPort unavailable, Port is already in use");
		close(sock_fd);
	}
       else{
		printf("\nBinding");

	        lis_check=listen(sock_fd,5);

        	if(lis_check<0)
        	        printf("\nListening failed");
		else
      			printf("\nlistening");

        	while(1){
                	printf("\nSERVER WAITING FOR NEW CONNECTION\n");
                	cliaddrlen=sizeof(cliaddr);
                	if(client_limit < CONNECTION_LIMIT){
                		newsock_fd=accept(sock_fd,(struct sockaddr*)&cliaddr,&cliaddrlen);
	
        	       		 if(newsock_fd<0)
                		        printf("\nClient not connected");
               			else{
					client_limit++;
	                		printf("CONNECTED TO CLIENT\n");
                			pthread_create(&serverThread,NULL,&client_thread,(void *)newsock_fd);
				}
			}else{
				do{
				}while(client_limit==5);
			}
        	}
		close(newsock_fd);
	}
	return 0;
}

void main(){

//memset(&g_provider_msg, 0, sizeof(struct t_provider_msg));
server();

}

/*i=strlen(buffer);
buffer[i]='\0';
strcpy(buf,buffer);
buf[strlen(buf)]='\0';
memset(buffer1,0,sizeof(buffer1));
str=strtok(buf,':');

if((strncmp(str,"START_SESSION",13)==0) || (strncmp(str,"INPUT",5)==0)){
session(buf);
}
else{
buffer1=User_Validation(buf);
buffer1[strlen(buffer1)] = '\0';
if(strlen(buffer1)<=5){
                        ibuffer=atoi(buffer1);
                        if((ibuffer>=1001) && (ibuffer<=3000))
                        uid=ibuffer;
//if((ibuffer>=7000) && (ibuffer<=9000))
        // strcpy(ssid,buffer1);

                strcpy(buffer2,id_validation(buffer1));
write(newsock_fd,buffer2,MAX);
                }*/
/*else if(buffer[strlen(buffer)-1] == '$'){
i=strlen(buffer);
buffer[i]='\0';
strcpy(buf,buffer);
buf[strlen(buf)]='\0';
        memset(buffer1,0,sizeof(buffer1));
buffer1=svc_provider(buf,ssid);
buffer1[strlen(buffer1)] = '\0';
msg_len=write(newsock_fd, buffer1, MAX);
               printf("\n%d",msg_len);
}*/

