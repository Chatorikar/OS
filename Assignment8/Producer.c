#include <sys/shm.h>
#include "shm_com.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char const *argv[])
{
	int running = 1 ;

	void *shared_memory = (void *)0;

	struct shared_use_st *shared_stuff;
	char buffer[BUFSIZ];
	int shmid;

	shmid = shmget((key_t)1234 , sizeof(struct shared_use_st) ,0666 | IPC_CREAT);

	if (shmid == -1)
	{
		printf("failed to get shared Memory\n" );
		exit(EXIT_FAILURE);
	}

	shared_memory = shmat(shmid , (void * )0 , 0);
	printf("Memory Attached Sucessfully %X \n" ,(int)shared_memory );
	shared_stuff = (struct shared_use_st *)shared_memory;

	while(running)
	{
		while(shared_stuff->count == 1)
		{
			sleep(1);
			printf("Waiting for Client\n");

		}
		printf("Enter Some text : \n");
		fgets(buffer,BUFSIZ,stdin);

		strncpy(shared_stuff->Memory_Content , buffer , TEXT_SIZE);
		shared_stuff->count = 1;

		if(strncmp(buffer,"end",3) == 0)
		{
			running = 0;
		}
	}

}

