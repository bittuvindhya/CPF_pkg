#ifndef __CPFAPI__H_
#define __CPFAPI__H_
#define PORT 2020
struct get_list{
	char iSid[5];
	char name[12];
	char type[12];
	char status[12];
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
	
};

struct ifconfig_data1
{
        char *interface;
        char *HW_address;
        char *IPV4_address;
        char *IPV6_address;
        char *mtu;
        char *link_status;
};

struct session{
	char iSession_id[6];
	char iSid[5];
	char iUid[5];
};
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
//int exuid_retrive();
int sid_retrive();
char* sub_subscribe(char *);
int parser_engine();
char* id_validation(char*);
int  start_session_validation(char *,int);
int  start_validate_buffer(char *,int);
int start_length_checking(char *,int);
int start_session( char *);
int sessionid_retrive();

//int sub_retrive();

#endif
