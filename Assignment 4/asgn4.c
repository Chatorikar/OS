#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

pthread_t *consumers;
pthread_t *producers;
void producer(pthread_t self);
sem_t buf_mutex,empty_count,fill_count;
int *buf,buf_pos=-1,prod_count,con_count,buf_len;
int produce(pthread_t self){
	int i=0;
	int p=1+rand()%40;
	while(!pthread_equal(*(producer+i),self) && i<prod_count)
		i++;
	printf("Producer ''%d'' Produces %d",i+1,p);
	return p;
}
void consume(int p,pthread_t self){
	int i=0;
	int p=1+rand()%40;
	while(!pthread_equal(*(producer+i),self) && i<con_count)
		i++;
	printf("Buffer : ");
	for(int j=0;j<=buf_len;j++)
		printf("| %d ",*(buf+j));
	printf("\nConsumer ''%d'' Consumes %d\nCurrent Buffer Length : ",(i)%con_count+1,p,buf_pos);
	printf("\n-----------------------------------------\n");
}

void producer(pthread_t self){
	while(1){
		int p=produce(pthread_self());
		sem_wait(&empty_count);
		sem_wait(&buf_mutex);
		++buf_pos;
		*(buf+buf_pos)=p;
		sem_post(&buf_mutex);
	}
}
