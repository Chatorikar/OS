#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

void Display(int *a , int n)
{
    printf("\n\n Sorted Array : ");
    for(int i = 0 ; i < n ; i++)
    {
        printf(" %d" ,a[i]);
    }
    printf("\n");
}


void Bsort(int *a , int n)
{
    int temp;

    for(int i = 0 ; i < n ; i++)
    {
        for(int  j = 0 ; j < n ;j++)
        {
            if(a[i] < a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

void Insertion(int *a , int n)
{
    int last , j;
    if(n <= 1)
        return;
    
    Insertion(a , n-1);

    last = a[n-1];
    j = n-2;

    while( j >= 0 && a[j] > last )
    {
        a[j+1] = a[j];
        j--;
    }

    a[j+1]=last;
}

int main()
{
    pid_t pid;
    int i , j ;
    char buffer[50];
    int *a , n , *b , choice;

    printf("\n\n Enter the Size  : ");
    scanf("%d" , &n);

    a = (int *)malloc(n*sizeof(int));
    b = (int *)malloc(n*sizeof(int));

    for(i = 0 ; i < n ; i++)
    {
        printf(" A[%d]  :  " , i+1);
        scanf("%d" ,&a[i] );
        b[i] = a[i]+5;
    }

    printf("\n\n 1) Normal Excuetion \n 2) Zombie \n 3) Orphan \n Enter your Choice  : ");
    scanf("%d" , &choice);

    switch (choice)
    {
    case 1:
        pid = fork();
        if(pid == -1)
        {
            perror("Error : Fork Error ");
            exit(EXIT_FAILURE);
        }
        else if( pid > 0)
        {
            // Parent Process

            printf("\n\n In Parent Process : %d\n", getpid());
            printf("\n\n Let's Sort Array A using Bubble Sort ");
            Display(a,n);
            sleep(1);
            Bsort(a,n);
            Display(a,n);
            wait(NULL); // Wait for Child to avoid Zombie Condtion
            printf("\n\n================Parent Done=======================\n");
            
        }
        else
        {
            //Child

            printf("\n\n In Child Process : %d\n", getppid());
            printf("\n\n Child Process ID : %d\n", getpid());

            printf("\n\n Let's Sort Array B using Insertion Sort ");
            Display(b,n);
            sleep(2);
            Bsort(b,n);
            Display(b,n);
            printf("\n\n================Child Done=======================\n");
        }
        
        break;
    case 2:
         pid = fork();
         if(pid == -1)
         {
            perror("\n\n Error : Fork() System Call");
         }
         else if( pid > 0)
         {
            printf("\n\n In Parent Process  :  %d" ,getpid() );
            printf("\n\n Let's Sort Array A using Bubble Sort");
            Display(a,n);
            printf("\n\n Parent is in Sleep");
            sleep(5);
            printf("\n\n After Sleep");
            Bsort(a,n);
            Display(a,n);
            sleep(5);
            snprintf(buffer , 50 , "ps -elf | grep %d" , pid );
            system(buffer);

            printf("\n\n Parent Going to Sleep ");
            sleep(8);
            wait(NULL);
            snprintf(buffer , 50 , "ps -elf | grep %d" , pid );
            system(buffer);
            printf("\n\n================Parent Done=======================\n");
                    
            

         }  
         else
         {
            printf("\n\n In Child Process  :  %d" ,getppid() );
            printf("\n\n Child Process ID : %d\n", getpid());
            printf("\n\n Let's Sort Array B using Insertion Sort");
            Display(b,n);
            printf("\n\n Child is in Sleep");
            sleep(2);
            printf("\n\n After Sleep");
            Insertion(a,n);
            
            printf("\n\n================Child Done=======================\n");
            exit(0);
         }
         


         case 3:
            pid = fork();

            if(pid == -1)
            {
                perror("\n\n Error :  Fork()");
                
            }
            else if (pid > 0)
            {   
                printf("\n\n In Parent Process  :  %d" , getpid());
                printf("\n\n Let's Sort Array Using A using Bubble Sort ");
                Display(a,n);
                printf("\n\n Parent is going to sleep");
                sleep(2);
                printf("\n\n After sleep");
                Display(a,n);
                Bsort(a,n);
                printf("\n\n Now I am going ");
                exit(0);
            }
            else
            {
                printf("\n\n In Child Process :  %d", getppid());
                printf("\n\n Child Process ID  : %d" , getpid());
                printf("\n\n Let's Sort using Insetion Sort");
                Display(b,n);
                Insertion(b,n);
                Display(b,n);
                printf("\n\n Child Is going to Sleep");
                sleep(5);
                printf("\n\n Child is Become Orphan Now : %d" , getpid());
                printf("\n\n Wating for Init Process" );

                sleep(1);
                printf("\n\n Adopted by Init process %d" ,getppid() );
                printf("\n\n In [   Root   ] :  %d" , getppid());
                snprintf(buffer , 50 , "ps -f  %d" , getppid() );
                system(buffer);
                
            }
            
            
    default:
        break;
    }
    
}