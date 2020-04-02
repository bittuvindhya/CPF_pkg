#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CPF_CONFIG_FILE	  "cpf_config.cfg"

void* open_config(char *pPath)
{
	FILE* fpConfigFile;
	char strConfigFile[512];
	char strCurrDir[255];

	memset(strConfigFile, 0, sizeof(strConfigFile));
	memset(strCurrDir, 0, sizeof(strCurrDir));

	if (getcwd(strCurrDir, sizeof(strCurrDir)) == NULL){
		fprintf(stderr, "ERROR: Unable to get current working dir\n");
		return NULL;
	}

	strcpy(strConfigFile, strCurrDir);
	strcat(strConfigFile, "/");
	strcat(strConfigFile, CPF_CONFIG_FILE);

	fprintf(stdout, "INFO: Config file: (%s)\n", strConfigFile);

	fpConfigFile = fopen(strConfigFile, "r");

	if (fpConfigFile == NULL) {
		fprintf(stderr, "ERROR: Unable to open configuration file\n");
		return NULL;
	}

	return (void *)fpConfigFile;
}


void close_config(void *pHandle)
{
	FILE * fpConfigFile;

	fpConfigFile = (FILE *)pHandle;

	fclose(fpConfigFile);
}


char *get_config (void *, char *, char* );

// File Handle
// String to locate
// default value to return
//
//
//
