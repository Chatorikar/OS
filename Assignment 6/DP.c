#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

// Philosopher Number
#define N 5


enum
{
    THINKING ,
    EATING ,
    HUNGRY
}state[N];

int eatcount[N] ={0};
pthread_mutex_t lock;
sem_t chopstick[N];

void think(int i)
{
    if(state[i] == THINKING)
    {
        int temp = rand()%3;
        if(temp == 0)
            temp = 2;
        printf("\n Philospher %d : Thinking \n" , i+1);
        sleep(temp);
        state[i] = HUNGRY;
    }
}

void takechopstic(int i)
{
    sem_wait(&chopstick[i]);
    sem_wait(&chopstick[(i+1)%N]);
}

void putchopstick(int i)
{
    sem_post(&chopstick[i]);
    sem_post(&chopstick[(i+1)%N]);

}

void eating(int i)
{
    int temp = rand()% 3;
    if(temp == 0)
        temp = 2;
    
    if( state[i] == HUNGRY && state[(i+1)%N] != EATING && state[(i + N-1)%N] != EATING)
    {
        state[i] = EATING;
        printf("\n\n Philopher %d Eating ",i+1);
        takechopstic(i);

        sleep(temp);
        
        eatcount[i]++;
        printf("\n\n %d Done with Eating " ,i+1);

        putchopstick(i);
        state[i] = THINKING;

        pthread_mutex_lock(&lock);
        printf("\n\n\n ==========================");
        printf("\n\n EatCount is  [  ");

        for(int j = 0 ; j < N ; j++)
        {
            printf(" %d" , eatcount[j]);
        }
        printf("  ] ");
        printf("\n\n\n ==========================");
        pthread_mutex_unlock(&lock);
    }
}

void * philospher(void * num)
{
     int i = *(int*)num;
     
    while(1)
    {
        think(i);
        eating(i);
    }
}


int main()
{
    int *arg  , result , i;
    pthread_mutex_init(&lock,NULL);
    pthread_t philosphertherad;

    for(int i = 0 ; i < N ; i++ )
    {
        sem_init(&chopstick[i] , 0 , 1);
    }

    for( i =  0 ; i < N ;i++)
    {
        arg = (int *)malloc(sizeof(int));
        *arg = i;
        pthread_create(&philosphertherad , NULL , philospher , (void *)arg);
    }

    for(i = 0 ; i < N ; i++)
    {
        if( pthread_join(philosphertherad,NULL) != 0)
        {
            printf("\n\n Error in Thhread joining");
        }
        

    }

    
}
