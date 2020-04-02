#define PORT 2020
int reg_usr_validation(char *);
void validate_buffer(char *);
void command_validation(char *);
int reg_svc_validation(char *,int);
void svc_validate_buffer(char *,int);
void id_validation(char* );
int main_validation(char *,int);
int command_checking(char *);
int length_checking(char *);
int svc_length_checking(char *,int);
int  svc_list_validation(char *,int);
int  svc_list_validate_buffer(char *,int);
int svc_list_length_checking(char *,int);
int  subscribe_validation(char *,int);
int  subscribe_validate_buffer(char *,int);
int subscribe_length_checking(char *,int);


