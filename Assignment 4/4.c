#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<semaphore.h>
#include<pthread.h>

int readcount = 0;
sem_t mutex  , rwlock;
int data=0;
void *reader(void *arg);
void *writer(void *arg);
int c = 0;
int main()
{
    int r =  5 , w = 5 , i  , j , *arg;
    
    pthread_t readerT , writerT;
    sem_init(&mutex , 0 , r);
    sem_init(&rwlock,0,1);

    for(i = 0 ; i < r ; i++)
    {
        arg = (int *)malloc(sizeof(int));
        *arg = i;
        pthread_create(&readerT , NULL , reader , arg);
    }

    for(i = 0 ; i < w ; i++)
    {
        arg = (int *)malloc(sizeof(int));
        *arg = i;
        pthread_create( &writerT , NULL , writer , arg);
    }

    pthread_join(readerT,NULL);
    pthread_join(writerT,NULL);
    
}
void *reader(void *arg)
{
    int *num = (int *)arg;
    int temp;
    temp = rand()%3;
        if(temp == 0)
            temp = 2;
    while(1)
    {
        
        sleep(temp);
       
        sem_wait(&mutex);

        printf("\n\n {  %d  }   Reader Before The Crtical Section",*num);

        readcount++;
        if(readcount == 1)
            sem_wait(&rwlock);
        
        

        sem_post(&mutex);
        c++;
        printf("\n\nNo. of People  in CS :  %d   :  [   %d   ] In critical Section Reader reads data  ---> ((  %d  ))" ,c , *num ,data );
        
        sem_wait(&mutex);

        sleep(1);
         c--;
        printf("\n\n %d (  %d  ) Leaves Crtical Section " ,c , *num);
        
        readcount--;
       
        if(readcount == 0)
            sem_post(&rwlock);
        sem_post(&mutex);
    }


}

void *writer( void *arg)
{
    int *num = (int *)arg;
    int temp;

    while(1)
    {
        temp = rand()%3;
        if(temp == 0)
            temp = 2;
        sleep(temp);

        sem_wait(&rwlock);

        printf("\n\n\t\t\t\t\t\t\t Writer Enter into Critical Section %d", *num);
        //sleep(temp);
        data++;
        
        c++;
        
        printf("\n\n\t\t\t\t\t\t\t No. of People  in CS :  %d   :  Writer {   %d  }  writes data  ====>   [   %d   ] " ,c ,*num, data);
        
        c--;
        
        printf("\n\n\t\t\t\t\t\t\tNo. of People  in CS :  %d   :   Writer [  %d ] leaves crtical Section   " ,c, *num);

        
        sem_post(&rwlock);
    }
}

