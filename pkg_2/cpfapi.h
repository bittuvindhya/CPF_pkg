#ifndef __CPFAPI__H_
#define __CPFAPI__H_
#define PORT 2020
#define PORT_NO 2022

struct get_list{
	char iSid[5];
	char name[12];
	char type[12];
	char status[12];
	char field[50];
	char sessiontype[12];
	char iUid[6];
};
struct uid_list{
	char name[24];
	char mailid[24];
	char iUid[6];
};

struct subscribe{
	char iSid[5];
	char iUid[5];
	char iSubid[5];
};
	
struct service{
	void *pHandle;
	char* (*getname)();
	char* (*gettype)();
	char* (*getstatus)();
	char* (*getuid)();
	char* (*getfield)();
	char* (*getsessiontype)();
	char* (*perform)(char*); 	
};

/*struct ifconfig_data1
{
        char *interface;
        char *HW_address;
        char *IPV4_address;
        char *IPV6_address;
        char *mtu;
        char *link_status;
};*/

struct session{
	char iSession_id[6];
	char iSid[5];
	char iUid[5];
};

typedef enum{
	       	T_NONE=0,
	       	T_REGISTER_USER,
		T_REG_SVC,
	       	T_GET_SVC_LIST,
	       	T_SUBSCRIBE_SVC,
	       	T_START_SESSION,
	       	T_SVC_INPUT,
	       	T_END_SESSION
} MSG_TYPE;

struct t_provider_msg {
	MSG_TYPE type;
	int session_id;
	int pro_response;
	char input[2048];
	char response[2048];
};

struct t_provider_msg   g_provider_msg;

//  g_provider_msg.type = T_START_SESSION;
//
//
//

int uim(char *);
int svc_reg(char * );
char* get_svc_list(char *);
int get_svc();

/*void sub_subscribe(char []);
void start_session(char []);
void end_session(char []);*/
char* User_Validation(char *);
char* Command_Interpreter(char *);
char* getDecStr(char*,int,int);
int uid_retrive();
int request_validation(char *, int *, char *);
int process_cpf_req(int *,char *, char *);
int process_provider_req(int *,char *, char *);
int sid_retrive();
char* sub_subscribe(char *);
int parser_engine();
char* id_validation(char*);
int  start_session_validation(char *,int);
int  start_validate_buffer(char *,int);
int start_length_checking(char *,int);
int generate_session_id( char *);
int sessionid_retrive();
int exist_sid(char *);
char *svc_provider(char *,char *);
char* svc_field(char* );
int request_validation(char *,int *,char *);
int uid_exist(char *);
//int sub_retrive();
char *session();
char *ssid;
int req_type;
char *req_input;
char *resp_output;

#endif
