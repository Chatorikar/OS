#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    // Fork returns process id
    // in parent process
    int child_pid = fork();

    // Parent process
    if (child_pid > 0){

      printf("PARENT IS ON %d\n ",getppid() );
        sleep(10);
        while(1){}
        printf("Challo is Django BOI\n" );
      }
    else{
        printf("Child IS ON  %d\n ",getpid() );
        printf("process over child \n" );
        exit(-1);
    }
    return 0;
  
}
