#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#define THINKING 0
#define EATING 1
#define HUNGRY 2
#define Total_Philospher 5
#define left (Philosopher_Num + 4) % Total_Philospher
#define right (Philosopher_Num + 1) % Total_Philospher


sem_t mutex;
sem_t S[Total_Philospher];


int Philosopher_state[Total_Philospher];
int phil[Total_Philospher] = { 0, 1, 2, 3, 4 };

void TEST(int Philosopher_Num)
{
  if( Philosopher_state[Philosopher_Num] == HUNGRY && Philosopher_state[left] != EATING && Philosopher_state[right] != EATING )
  {
    sleep(2);
    printf("Philosopher %d takes fork %d and %d\n", Philosopher_Num , left + 1, right + 1);

    printf("Philosopher %d is Eating\n", Philosopher_Num + 1);
    sem_post(&S[Philosopher_Num]);
  }
}


void Take_ChopStick(int Philosopher_Num)
{
    sem_wait(&mutex);

    printf("Philosopher %d is Hungry\n", Philosopher_Num + 1);

    sem_post(&mutex);

    sem_wait(&S[Philosopher_Num]);

    sleep(1);
}


void Put_Fork(int Philosopher_Num)
{
  sem_wait(&mutex);

   Philosopher_state[Philosopher_Num] = THINKING;

   printf("Philosopher %d putting fork %d and %d down\n",  Philosopher_Num + 1, left + 1, Philosopher_Num + 1);
   printf("Philosopher %d is thinking\n", Philosopher_Num + 1);

   TEST(left);
   TEST(right);

   sem_post(&mutex);
}

void* philospher(void* num)
{

    while (1) {

        int* i = num;

        sleep(1);
        printf("Eating %d" , num);
        Take_ChopStick(*i);

        // printf("Eating %" , num);
        sleep(0);

        Put_Fork(*i);
    }
}

int main()
{
  int i;
  pthread_t thread_id[Total_Philospher];


  sem_init(&mutex, 0, 1);

  for (i = 0; i < Total_Philospher; i++)

      sem_init(&S[i], 0, 0);

  for (i = 0; i < Total_Philospher; i++) {
      pthread_create(&thread_id[i], NULL,   philospher, &phil[i]);

      printf("Philosopher %d is thinking\n", i + 1);
  }

  for (i = 0; i < Total_Philospher; i++)
      pthread_join(thread_id[i], NULL);
}
