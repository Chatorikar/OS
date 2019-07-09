
/*Implement the C program in which main program accepts an integer array. Main
program uses the FORK system call to create a new process called a child process.
Parent process sorts an integer array and passes the sorted array to child process
through the command line arguments of EXECVE system call. The child process
uses EXECVE system call to load new program that uses this sorted array for
performing the binary search to search the particular item in the array.*/

   /* for 'execve' */ 
#include <stdio.h>      /* for 'printf' and 'NULL' */
#include <stdlib.h>     /* for 'errno' */
#include <string.h>
#include <unistd.h>


void Sorting(int *arr , int len)
{
	
	int temp;
   
    
    for(int i = 0 ; i < len ; i++){
    
    	for(int j = i ; j < len ; j++){
    		
    		if(arr[i] > arr[j]){

				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;	
    		
    		}
    	
    	}
    
    }

 
 
 printf("\n\n Sorted Array :");
 
 for (int i = 0; i < len; i++){
    	
    	
    	printf("%d ", arr[i] );
    }

}



int main(int argc, char const *argv[])
{
	
	int arr[50] , len ;
	char *pointer_array[10] = { "1" , "2" , "3"};
	char sprintf_buffer[50];

	printf("Enter the size of the array  :  \n");
	scanf("%d",&len);

	for (int i = 0; i < len; ++i)
	 {
	 	printf("a[%d] : ",i );
	 	scanf("%d",&arr[i]);
	 } 

	 printf("Array to be Sort :  \n");
	 for (int i = 0; i < len; ++i)
	 {
	 	printf("%d  ",arr[i] );
	 	
	 } 


	 printf("\n\n Execute Forking :  \n");

	 if (fork() == 0)  // Child Process Executing
	 {
	 	printf("\n\n Child Process ID :  %d \n",getpid() );
	 	
	 }
	 else{

	 	printf("\n\n Parent Process ID :  %d \n",getppid() );
	 	printf("\n\nSorting Done in Parent :  \n");
	 	Sorting(arr,len);
	 	printf("\n\n Calling Binary_Search : \n");
	 	execve("./Binary_Search.c" , pointer_array);


	 	
	 	printf("\n\n Converting Through Buffer \n");

	 	for (int i = 0; i < len; ++i)
	 	{
	 		
	 		sprintf ( sprintf_buffer[i], "%d", arr[i]);
	 		pointer_array[i] = sprintf_buffer[i];

			
	 	}

	 	printf("Printing in Buffer \n");
	 	
	 	for (int i = 0; i < len; ++i)
	 	{
	 		
			printf("%s\n", pointer_array); 
	 	}
		

	 }




	return 0;
}

