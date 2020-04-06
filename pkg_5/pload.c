#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.

#define PLUGIN_DIR "./plugins"
#define TRUE 1
#define FALSE 0

struct _hooks {
  char  p_name[255];
  void* handle;
  char* (*get_name_func)();
  char* (*register_func)();
  int   is_loaded;
} plugins[5];

int plugin_count = 0;

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void *myThreadFunc(void *vargp)
{
   unsigned int stop_flag = FALSE;

   do
   {
        struct dirent *de;

        DIR *dr = opendir(PLUGIN_DIR);

        if (dr == NULL)  // opendir returns NULL if couldn't open directory
        {
                printf("ERROR: Could not open current directory\n" );
                pthread_exit(NULL);
        }

        printf("INFO: Scanning directory for new plugin..\n");
        while ((de = readdir(dr)) != NULL)
        {
                unsigned int is_new_flag = TRUE;
                unsigned int index = 0;

                char ppath[255];

                // End loop file
                if (!strcmp(de->d_name, "stop")) {
                        printf ("INFO: found stop loop file.. quiting plugin watch thread.\n");
                        stop_flag = TRUE;
                        break;
                }

                if (strstr(de->d_name, ".so") == NULL) continue;

                memset(ppath, 0, sizeof(ppath));

                printf("%s\n", de->d_name);
                strcpy(ppath, PLUGIN_DIR);
                strcat(ppath, "/");
                strcat(ppath, de->d_name);


                // Check if the plugin is already exists
                for (index = 0; index < plugin_count; index++) {
                        if (strcmp(plugins[index].p_name, ppath) == 0) {
                                is_new_flag = FALSE;
                                break;
                        }
                }

                if (!is_new_flag) continue;

                printf("INFO: New plugin found.. Loading plugin.. (%s)\n", ppath);
                void* lib_handle = dlopen(ppath, RTLD_LAZY);
                if (!lib_handle) {
                        fprintf(stderr, "ERROR: Unabled to load plugin.. (%s)\n", dlerror());
                        continue;
                }

                memset(plugins[plugin_count].p_name, 0, sizeof(plugins[plugin_count].p_name));
                strcpy(plugins[plugin_count].p_name, ppath);

                plugins[plugin_count].handle = lib_handle;
             	
	     	*(void **)(&plugins[plugin_count].get_name_func) = dlsym(lib_handle, "getname");
                *(void **)(&plugins[plugin_count].register_func) = dlsym(lib_handle, "gettype");
                plugins[plugin_count].is_loaded = TRUE;

                printf("PLUG-IN NAME :=(%s)\n",plugins[plugin_count].get_name_func());
                printf("PLUG-IN TYPE :=(%s)\n",plugins[plugin_count].register_func());

                plugin_count++;
        }

        closedir(dr);
        sleep(10);

        if (stop_flag) break;

   } while (TRUE);

   printf ("INFO: Closing watch thead..\n");

   //pthread_cancel(pthread_self());
   pthread_exit(NULL);

   return 0;
}

int main()
{
   pthread_t thread_id;
   printf("Creating plugin watch thread..\n");
   pthread_create(&thread_id, NULL, myThreadFunc, NULL);

   pthread_join(thread_id, NULL);
   printf("Client Thread Ended\n");

   printf("INFO: Number of plugins.. (%d)\n", plugin_count);
   while (--plugin_count >= 0) {

        printf("INFO: Unloading plugin.. (%s)\n", plugins[plugin_count].p_name);
        dlclose(plugins[plugin_count].handle);
   }

   return 0;
}
