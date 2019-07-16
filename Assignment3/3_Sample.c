#include <stdio.h>
#include <pthread.h>

void *KidFunc(void *p)
{
	printf("Kit id is ===>  %d \n" , getpid());
}

int main(int argc, char const *argv[])
{
	pthread_t kid;
	pthread_create(&kid , NULL , KidFunc , NULL);
	printf("Parent ID id ==> %d \n" , getppid());
	pthread_join(kid,NULL);
	printf(" OK DONE \n");
	return 0;
}

// #include <stdio.h>
// #include <pthread.h>
// void *kidfunc(void *p)
// {
// printf ("Kid ID is ---> %d\n", getpid( ));
// }

// void main ( )
// {
// pthread_t kid ;
// pthread_create (&kid, NULL, kidfunc, NULL) ;
// printf ("Parent ID is ---> %d\n", getpid( )) ;
// pthread_join (kid, NULL) ;
// printf ("No more kid!\n") ;
// }