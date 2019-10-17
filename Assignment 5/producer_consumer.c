#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 40

// Producer Consumer alos called as ==> Bounded Buffer Problem

// Problem can occure is 
// 1) Overflow 
// 2) Underflow condition can occure solve by Binary semaphore 

// Critical Section in this problem is 1) Buffer and 

// Buffer Size

// In a multiprocessor environment, the most important reason for using Pthreads is to take
//	advantage of potential parallelism

/*
	
	* Difference between Semaphore and Mutex

	* Incase of mutex there will be owenership  i.e. it is locked critical section
	
	* Mutext is a object owned by thread so there is ownership in mutex. Mutex allow only one thread to access resource

	* Semaphore how many thread can be simultaneous access resources
	
	* Semaphore is a signalling mechanisam.It allow number of thread to access shared resource.

	* Semaphore all operation are atomic hence during down premtion is not allowed


	* What is semaphore ?
		It is mutual exclusion without busy waiting soluntion
		It is a blocking solution
		It block a process and wakeup the process	

	* Counting Semaphore 
	Postive value indicated total possible down operation can be done
	Negative value indicate total number of process block

	Basically sempahore is used to solve critcal section problem 

	it is simple integer

	wait() ==> reduces semaphore value by 1 

*/


// Problem can occure whent cosnumer {readcount} ==> This is not an atomic operation as result of this 
// there are two operation will be there 1) Read Count varible from regiseter and then decrement the count
// so if if before readcoun-- i.e. decrement the count if there is premition occure then consumber will wailt as 
// Producer is empty ..... somthing like thar
// This sitution can called as lost wakeup problem
//
/***********************So we are using semaphore to overcome this situation***************************************/

void line()
{
	printf("\n===============================================================\n");
}
//pthread stands for POSIX thread
//pthread_t is a type similar to int and it's created when you define it, not when you call pthread_create
//pthread_t is the data type used to uniquely identify a thread
//. All threads within a process share the same address space.

pthread_t producer , consumer; // Hence it is Created // declare thread 

pthread_mutex_t lock ;//= PTHREAD_MUTEX_INITIALIZER;
//Use the macro PTHREAD_MUTEX_INITIALIZER to initialize statically defined mutexes to their default attributes.
//Do not reinitialize or destroy a mutex lock while other threads are using the mutex. ====>>> Leads to DeadLock
//pthread_mutex_t is used to declare an object of type mutex.




// Indices for producer and consumer
int pid, cid;

sem_t full , empty; // Counting Semaphore 

/*
	* empty will be intitlize by Buffer Size Counting 

	* full will be intitlize by 0  ( As intitlly Buffer is empty )
*/

int buffer[BUFFER_SIZE]; //Critical Section

int pid, cid;

// it takes any void pointer and return void pointer
//because void pointer can be point to any data type 
// and can be return any data type
void *producer_thread(void *agv)
{
	int *num = (int *)agv;
	while(1)
	{
		
		
		int temp = rand() % 5 , i;

		temp = temp == 0 ? 2 : temp;

		 sleep(temp+2);

		// Give Ramdom sleep Observe behaviour

		/*
			* Cheack Whether Buffer is empty or not 
			
			* Enter Only if buffer is empty 
		*/	
		
		
		sem_wait(&empty);
		

		// Enter only when empty > 0 i.e. Buffer having some space for Producer

 		pthread_mutex_lock(&lock);
		

		// Particular Thread can take access to Critical Section ( producer thread )

		// Critical Section Start 
		
		buffer[pid] = temp;

		line();
		
		printf("Producer %d   ", *num);
		
		printf("\nBuffer : [ ");
		
		for(i = 0 ; i < BUFFER_SIZE ; i++)
		{	
			if(buffer[i] == 0)
				continue;
			printf("%d ",buffer[i] );
		}

		printf(" ] \n");

		//line();

		pid = ( pid + 1 ) % BUFFER_SIZE;

		// Critical Section End  
		
		// Leave Access to Critical Section
		pthread_mutex_unlock(&lock);
		
		sem_post(&full);

	}
}

void * consumer_thread(void *agv)
{	
	printf("In Consumer \n");
	int *num = (int *)agv;

	while(1)
	{
		
		int temp = rand() % 5 , i;

		temp = temp == 0 ? 2 : temp;

		sleep(temp+2);

		sem_wait(&full);

		pthread_mutex_lock(&lock);

		buffer[cid] = 0;
		
		cid = (cid + 1) % BUFFER_SIZE;		
		
		line();
		printf("Consumer %d " ,*num);
		
		printf("\nBuffer : [  ");
		
		for(i = 0 ; i < BUFFER_SIZE ; i++)
		{	if(buffer[i] == 0)
				continue;
			printf("%d ", buffer[i] );

		}
		printf(" ] \n");
		//line();
		
		

		pthread_mutex_unlock(&lock);

		sem_post(&empty); 
		

	} 
}



int main()  // Main Also a one thread
{
	int i , pro = 35 , con = 25 , result;
	
	int *agv;

	pid = cid = 0;

	// intitally both producer and consumer point to starting index of buffer

	// printf("\n Enter  Number of Producer :  ");
	// scanf("%d" ,&pro );


	// printf("\n Enter  Number of Consumer :  ");
	// scanf("%d" ,&con );

	result = sem_init(&empty ,0 , BUFFER_SIZE);
	
	

	//sem_init() returns 0 on success; on error, -1 is returned, and errno
    //  is set to indicate the error.
	
	//The sem_init() function is used to initialise the unnamed semaphore referred to by sem.
	
	//int sem_init(sem_t *sem, int pshared, unsigned int value);
	
	//A pointer to the sem_t object for the semaphore that you want to initialize.

	//If the value of pshared is zero, then the semaphore cannot be shared between processes. If the value of pshared is nonzero, then the semaphore can be shared between processes.
	
	//The initial value of the semaphore. A positive value (i.e. greater than zero) indicates an unlocked semaphore, and a value of 0 (zero) indicates a locked semaphore. This value must not exceed SEM_VALUE_MAX.
	
	// sem_init(&sem, 1, count);Initializing Semaphores With Interprocess Scope

	if(result == -1)
	{
		printf("Error :Empty Semaphore Intilization of Semaphore \n");
	}

	result = sem_init(&full ,0 , 0);

	if(result == -1)
	{
		printf("Error : Full Semaphore Intilization of Semaphore \n");
	}

	result = pthread_mutex_init(&lock,NULL);
	
	//int pthread_mutex_init( pthread_mutex_t* mutex, const pthread_mutexattr_t* attr );
	
	// If attr is NULL, the default mutex attributes are used;
	
	//When the mutex is initialized, the mutex is in an unlocked state
	
	//The mutex can be in memory that is shared between processes or in memory private to a process.

	if(result != 0 )
	{
		printf("Error : Mutex Intilization  \n");
	}


	printf("\n\n\n");

	for(i = 0 ; i < pro ; i++)
	{
		agv = (int *)malloc(sizeof(int));
		*agv = i;

		result = pthread_create(&producer , NULL , producer_thread , (void *)(agv));

		
		/*
				int pthread_create(pthread_t * __restrict__thread, 
                   const pthread_attr_t *attr, 
                   void *(*start_routine) (void *arg), 
          
                   void * __restrict__arg);
		
		* Creates a new thread within a process
		
        * pthread_t is the data type used to uniquely identify a thread. It is returned by pthread_create() and used by the application in function calls that require a thread identifier.         
		* Is the location where the ID of the newly created thread should be stored, or NULL if the thread ID is not required.
		
		* void *(*start_routine) (void *arg) for which function we want to execute the thread it is pointer to that thread 
		* Is the main function for the thread; the thread begins executing user code at this address.

		* void * __restrict__arg is an attribute passed to function which is to be called 
		* Is the argument passed to function.		
		 
		
		*/

		if(result != 0)
		{
			printf(" Error : While Creating a Producer %d \n", i );
		}

		printf(" %d : Producer is created successfully \n", i );
	}

	for (int i = 0; i < con; i++)
	{	
		agv = (int *)malloc(sizeof(int));
		*agv = i;

		result = pthread_create(&consumer,NULL , consumer_thread , (void *)(agv));

		if(result != 0)
		{
			printf(" Error : While Creating a Producer %d \n", i );
		}

		printf(" %d : Consumer is created successfully \n", i );

	}

	 result = pthread_join(producer, NULL);
	 result = pthread_join(consumer, NULL);

	 /*

		The function pthread_create is used to create a new thread, and a thread to terminate itself
		uses the function pthread_exit. A thread to wait for termination of another thread uses the
		function pthread_join
	
	 */



	return 0;	
}



