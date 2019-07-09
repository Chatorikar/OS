
#include<stdio.h>
#include<unistd.h>
int main()
{

 pid_t p;

/* create child process */
 p=fork();

 if(p==0) {
    /* fork() returns Zero to child */
    sleep(10);
 }
 printf("The child process pid is %d parent pid %d\n", getpid(), getppid());
/*parent/child waits for 20 secs and exits*/
 sleep(20);
 printf("\nProcess %d is done its Parent pid %d...\n", getpid(), getppid());

 return 0;
}
