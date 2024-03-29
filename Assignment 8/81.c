#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include "shm_com_2.h"


/* 
  The reason for the system scope is that you want two or more independent processes to have access to the same IPC resources. 
   So if you have two programs, both of which execute key = ftok("/home/beej/somefile", 'b');, both will get the same token 
   and can therefor access the same resources (semaphores, shared memory, message queues). 
   That's the whole point of Inter Process Communication.
*/
/*
Shared memory is a special case, where the same "real memory" is addressed from more than one process. 
The virtual addresses that "shmat" returns are local to each caller.
*/

int main()
{
  int shmid , running = 1;
  key_t key = ftok( "shm_com_2.h" , 65);
  int choice;
  char buffer[50];
  
  void *shared;
  
  struct shared_memory *sm;

  shmid = shmget(key,sizeof(struct shared_memory ) , 0666 | IPC_CREAT);
  
  shared = shmat(shmid , NULL ,0);

  sm = (struct shared_memory *)shared;
  
  snprintf(buffer , 25 , "ipcs -m | grep %d" ,shmid);

  system(buffer);

  while(running)
  { 
    if(sm->written == 1)
    {
      choice = 1;
    }
    else
    {
      printf("\n\n 1) Read \n 2) Write \n Enter choice  ");
      scanf("%d" ,&choice);
    }
    switch (choice)
    {
      case 1:
            printf("\n\n Message :  %s" , sm->shared_array);
            sm->written = 0;
            break;
      case 2:
            printf("\n\n Enter Message :  ");
            scanf("%s" , sm->shared_array);
            sm->written = 1;
            break;
      
      case 3:
            running = 0;
      default:
            break;
    }     
  } 

  snprintf(buffer , 25 , "ipcs -m | grep %d",shmid);
  system(buffer);

  if(shmdt(shared) == -1)
  {
    perror("\n\nMemory Detach Failed");
  }
  if(shmctl(shmid, IPC_RMID , 0) == -1)
  {
    printf("\n\n Memory Deletion Failed");
  } 
  
  snprintf(buffer , 25 , "ipcs -m | grep %d",shmid);
  system(buffer);
  
  exit(EXIT_SUCCESS);

}
