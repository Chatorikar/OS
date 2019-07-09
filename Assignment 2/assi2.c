#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    //create temp arrays
    int L[n1], R[n2]; 
  
    //Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    //Merge the temp arrays back into arr[l..r]
    i = 0; 		// Initial index of first subarray 
    j = 0; 		// Initial index of second subarray 
    k = l; 		// Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    //Copy the remaining elements of L[], if there are any
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    //Copy the remaining elements of R[], if there are any 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 
  
//Function to print array
void printArr(int arr[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n\n"); 
} 
  
void quicksort(int number[],int first,int last)
{
   int i, j, pivot, temp;

   if(first<last)
   {
      pivot=first;
      i=first;
      j=last;

      while(i<j)
      {
         while(number[i]<=number[pivot]&&i<last)
            i++;
         while(number[j]>number[pivot])
            j--;
         if(i<j)
         {
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
         }
      }

      temp=number[pivot];
      number[pivot]=number[j];
      number[j]=temp;
      quicksort(number,first,j-1);
      quicksort(number,j+1,last);
   }
}


int main()
{
	int i,arr[10],n,total;
	printf("Enter total number of elements: ");
	scanf("%d",&total);
	
	printf("\nEnter elements : \n");
	
	for(i=0;i<total;i++)
	{
		scanf("%d",&arr[i]);
	}
	
	printf("----MENU----\n1.Zombie\n2.Orphan\nEnter your choice : ");
	scanf("%d",&n);
	
	int pid;
	pid=getpid();
	printf("\nCurrent Process id is:\t%d", pid);
	printf("\nForking...\n");
	
	pid=fork();
	
	//---------------Zombie-----------------
	if(n==1)
	{	
		if(pid<0)
		{
			printf("\nProcess creation failed!");
			exit(-1);
		}
		else if(pid==0)
		{
			printf("\nChild Process started!");
			printf("\nProcess ID is: %d", getpid());
			printf("\nParent Process ID is: %d\n", getppid());
			mergeSort(arr,0,total-1);
			printf("\nSorted Array: ");
			printArr(arr,total);
			printf("\nZombie!!\n");		
		}
		else
		{
			sleep(5);
			printf("\nParent Process");
			printf("\nProcess ID is:\t%d", getpid());
			printf("\nParent Process ID is:\t%d\n", getppid());
			quicksort(arr,0,total);
			printf("\nSorted Array:\t");
			printArr(arr,total);
			system("ps -elf | grep a.out");
		}
	}
	
	//----------------Orphan-------------------
	else if(n==2)
	{		
		if(pid<0)
		{
			printf("\nProcess creation failed!");
			exit(-1);
		}
		else if(pid==0)
		{
			
			printf("\nChild Process!!");
			printf("\nProcess ID is:\t%d", getpid());
			printf("\nParent Process ID is:\t%d\n", getppid());
			
			mergeSort(arr,0,total-1);
			printf("\nSorted Array: ");
			printArr(arr,total);
			
			printf("\nChild is sleeping!!\n");
			sleep(5);
			
			printf("\nBack to Child Process\n");
			printf("\nProcess ID is:\t%d", getpid());
			printf("\nParent Process ID is:\t%d\n", getppid());
			printf("Orphan!!\n");
			system("ps -elf | grep a.out");
		}
		else
		{	
			system("wait");	
			printf("\nParent Process started!");
			printf("\nProcess ID is:\t%d", getpid());
			printf("\nParent Process ID is:\t%d\n", getppid());
			
			quicksort(arr,0,total);
			printf("\nSorted Array:\t");
			printArr(arr,total);
			printf("\nParent is dying!!\n");
		}
	}
	return 0;
}
