#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

void Sort(int *arr , int len)
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



 printf("Sorted Array :");

 for (int i = 0; i < len; i++){


    	printf("%d ", arr[i] );
    }

}


int main(int argc , char *argv[])
{

	char *newargv[] = { NULL, "hello", "world", NULL };
	 newargv[0] = argv[1];
	int n = 0;
	int arr[50];
    printf("Enter Size of the Array \n");
    scanf("%d" , &n);

    for (int i = 0; i < n; i++)
    {
    	printf("Enter Element a[%d]  :  " , i );
    	scanf("%d" , &arr[i]);
    }



    Sort(arr,n);

		if(argc != 2){

			fprintf(stderr , " Usage : %s < File To Be Execute \n" , argv[0] );
		}

		execve(argv[1] , newargv , NULL);
}
