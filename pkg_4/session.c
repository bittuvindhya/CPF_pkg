#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include "cpfapi.h"
#define MAX 2048
struct ps_thread ps;

char* session(char *cBuffer){
	int session_id = 0;
        char *buf;
	char *command;
	char *str;
	int i;

	command=strtok(cBuffer,':');
	str=strchr(cBuffer,':');

	if(strcmp(str,"START_SESSION")==0){
		strcpy(ps.type_of_msg,"START_SESSION");
		buf=start_session(str);
		session_id =atoi(buf);
		ps.session_id=session_id;
		

	

