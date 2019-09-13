
#include "shm_com.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main(int argc, char const *argv[])
{
	
	int running = 1;
	void *shared_memory = (void *)0;
	int shmid;
	
	struct shared_use_st *shared_stuff;
	
	srand((unsigned int)getpid());

	shmid = shmget((key_t)1234 , sizeof(struct shared_use_st),0666 | IPC_CREAT);

	


	if(shmid == -1)
	{
		printf("Share memory are not allocated Sucessfully\n");
		exit(EXIT_FAILURE);
	}	

	shared_memory = shmat(shmid , (void *)0 , 0 );
	/*The second parameter of shmat is, shm_addr , is the address at which the shared memory is to be attached to the
current process. This should almost always be a null pointer, which allows the system to choose the
address at which the memory appears.*/
	
	if(shared_memory == (void *)-1)
	{
		printf("Memory Cannot Attched...Shmat Function Falied \n");
		exit(EXIT_FAILURE);
	}	

	printf("Memory Attched Sucessfully at %X \n", (int)shared_memory);


	shared_stuff = (struct shared_use_st *)shared_memory;
	shared_stuff->count = 0;
	while(running)
	{
		if(shared_stuff->count)
		{
			printf("You Wrote %s \n",shared_stuff->Memory_Content);
			sleep( rand() % 4 ); /* make the other process wait for us ! */
			shared_stuff->count = 0;
			if(strncmp(shared_stuff->Memory_Content,"end",3) == 0)
					running = 0;
			
		}
	}


	if(shmdt(shared_memory) == -1)
	{
		fprintf(stderr, "Shmdt Falied \n");
		exit(EXIT_FAILURE);
	}

	if(shmctl(shmid,IPC_RMID , 0) == -1 ){
		fprintf(stderr, "shmctl(IPC_RMID) Falied  \n");
		exit(EXIT_FAILURE);
	}


	exit(EXIT_SUCCESS);

}