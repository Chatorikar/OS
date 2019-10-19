#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<semaphore.h>
#include<pthread.h>

sem_t mutex , rwlock;
int readcount = 0;
int data;

void * R_fun(void *arg)
{
    int *num = (int *)arg;
    int temp;

    while(1)
    {
        temp = rand()%3;
        if(temp == 0)
            temp = 2;
        sleep(temp);
        sem_wait(&mutex);

        printf("\n\n [ %d  ] : Reader Before Crtical Section \n" , *num);    
        readcount++;
        
        if(readcount == 1)
            sem_wait(&rwlock);
        
        
        
        sem_post(&mutex);

        printf("\n\n (  %d  ) : Reader in Crtical Section Reads Data :====> %d \n" , *num , data);
        sleep(2);
        
        
        sem_wait(&mutex);
        
        printf("\n\n { %d  } : Reader Leaves : %d \n" , *num , data);
        
        readcount--;
        
        if(readcount == 0)
            sem_post(&rwlock);

        sem_post(&mutex);
    }

}


void *W_fun(void *arg)
{
    int *num = (int *)arg;
    while(1)
    {
        int temp = rand()%3;
        if(temp == 0)
            temp = 2;
        sleep(temp);

        sem_wait(&rwlock);

        
        printf("\n\n\t\t\t\t\t\t [ %d ] Writer in Crictical Section  :",*num);
        data++;
        printf("\n\n\t\t\t\t\t\t [%d ] Writer  Update Data :=====>  %d" , *num , data);
        printf("\n\n\t\t\t\t\t\t { %d } Writer Leaves Crictical Section  :",*num);


        sem_post(&rwlock);

    }

}

int main()
{
    
    int *arg;
    sem_init(&mutex ,0, 1);
    sem_init(&rwlock ,0,1);

    pthread_t reader ;
    pthread_t writer;
    int r = 5 , w = 5;

    for(int i = 0 ; i < r ; i++)
    {   
        arg = (int *)malloc(sizeof(int));
        *arg = i;
        pthread_create(&reader , NULL , R_fun , arg);
    }

    for(int i = 0 ; i < w ; i++)
    {
        arg = (int *)malloc(sizeof(int));
        *arg = i;
        pthread_create(&writer , NULL , W_fun , arg);
    }

    pthread_join(reader,NULL);
    pthread_join(writer,NULL);
    
}
