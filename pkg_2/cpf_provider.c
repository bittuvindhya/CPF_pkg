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
#define server_ip "127.0.0.1"
#define MAX 2048

char *cSession_id;
bool flag_A = 0;
bool flag_B = 0;
void *send_provider_msg(void *);

int process_provider_req (int* req_type, char *input, char *output)
{
	pthread_t provider_thread_id;
	int session_id =0;

	if(req_input != NULL){

		if(*req_type == T_START_SESSION){
			flag_A = 0;
			flag_B = 0;
			printf("\n inside T_START_SESSION");
			session_id = generate_session_id(req_input);
			printf("\n session__id =%d",session_id);
			g_provider_msg.session_id = session_id;
			g_provider_msg.type = T_START_SESSION;
			printf("\n structure populate=%d type=%d",g_provider_msg.session_id,g_provider_msg.type);
			pthread_create (&provider_thread_id, NULL, &send_provider_msg,NULL);
		} 

		else if(*req_type == T_SVC_INPUT){
			strcpy(g_provider_msg.input,req_input);
			flag_B = 1;

			strcpy(resp_output,g_provider_msg.response);
		} 

		else if(*req_type == T_END_SESSION){
			//strcpy(resp_output,sub_resp);
		}

		// Wait till provider processed msg and responded
		do {
			sleep (10);
		} while (flag_A != 1);
		flag_A = 0;
	}

	return 0;
}


// Provider thread created and the provider message being processed here
void *send_provider_msg(void *varg) {

	if (g_provider_msg.type != T_START_SESSION) {
		// Error:  Incorrect message type
		return NULL;
	}
	
	// STEP-1 : Connect to Provider
	else{
		printf("\nINFO:inside send_provider_msg");
		int sock_fd=0,msg_len=0,value=0,uid=0,ibuffer=0;
		struct sockaddr_in servaddr;
		char buffer[MAX],buffer2[MAX];
		char* buf=(char*)malloc(MAX*sizeof(char));
		sock_fd=socket(AF_INET,SOCK_STREAM,0);
	
		memset(&servaddr,0,sizeof(servaddr));
		servaddr.sin_family=AF_INET;
		servaddr.sin_addr.s_addr=inet_addr(server_ip);
		servaddr.sin_port=htons(PORT_NO);
	
		value = connect(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
		if(value <= 0 ){
			return value;
		}
		else
			printf("\nConnecting to server....");
		memset(&buffer2, 0, sizeof(buffer2));
		memset(&buffer,0,sizeof(buffer));

		msg_len=read(sock_fd,buffer2,MAX);
		printf("%s",buffer2);
		// STEP-2 : go into processing loop
		
		do {
			
			// STEP-3 : Send message to provider (based on structure)

			if (g_provider_msg.type != T_START_SESSION) {
				strcpy(buf,"START_SESSION:");
				cSession_id = getDecStr(cSession_id,4,g_provider_msg.session_id);
				strcat(buf,cSession_id);
				printf("\n In new provider thread buf--->%s",buf);
			}
			
			else if(g_provider_msg.type != T_SVC_INPUT){
				strcpy(buf,"INPUT:");
				strcat(buf,g_provider_msg.input);

			}
		
			else{
				printf("\n Error in reading structure inside thread function");
			}
			
			printf("\nINFO:inside send_provider_msg buf --->%s",buf);
			write(sock_fd, buf,MAX);

			// STEP-4 : Receive provider response

			memset(&buf,0,sizeof(buf));
			msg_len=read(sock_fd,buffer,MAX);
			printf("%s\n",buffer);
			
			// STEP-5 : Populate the response into message structure
		
			if(strncmp(g_provider_msg.response,"OK",2)==0) {
				g_provider_msg.pro_response = 1;
			}
			else if(strncmp(g_provider_msg.response,"NOT AVAILABLE",13)==0) {
				g_provider_msg.pro_response = 2;
			}
			
			else {
				printf("\n Error in input from provider ");
			}

			flag_A = 1;

			// STEP-6 : Hold the thread till next message for provider

			do {
				sleep (10);
			} while (flag_B != 1);

			flag_B = 0;
			

	} while (g_provider_msg.type != T_END_SESSION);

	// STEP-7 : Send message to provider (based on structure)

	// STEP-8 : Receive provider response

	// STEP-9 : Close provider connection

	// STEP-10 : Set response code to SUCCESS

	//flag_A = 1;
	}
	return NULL;
}




		
