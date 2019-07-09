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

        printf("PARENT IS ON %d \n ",getppid() );
        printf("Parent is Completed \n" );
      }
    else{

        printf("Child IS ON  %d\n ",getpid() );
        sleep(5);
        printf("PARENT ID %d \n ",getppid() );
        printf("process over child \n" );
        exit(-1);
    }
    return 0;
    
}
