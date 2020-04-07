#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

pthread_mutex_t lock;					//mutex creation
int exclusion=0;

void *producer(void *arg)					//producer part
{
       // pthread_mutex_lock(&lock);				//locking mutex
        scanf("%d",&exclusion);
	if(exclusion == 10)
       		 pthread_mutex_lock(&lock);
	printf("\n producer produced %d",exclusion);
}

void *consumer(void *arg)					//consumer part
{
        if(exclusion == 10)
 		printf("\n consumer comsumes %d",exclusion);
        pthread_mutex_unlock(&lock);				//unlocking mutex
	
}

void main()
{

        pthread_t pid,cid;					//creating thread
        char choice;
        while(1)
        {
        	pthread_create(&pid,NULL,producer,NULL);
                pthread_create(&cid,NULL,consumer,NULL);
                pthread_join(pid,NULL);
                pthread_join(cid,NULL);
        }
        pthread_mutex_destroy(&lock);			//destroy

}

