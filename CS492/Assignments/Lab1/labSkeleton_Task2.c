/*
I pledge my honor that I have abided by the Stevens Honor System.
Catherine Javadian
Kaitlynn Prescott 
Brianne Trollo
*/
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <errno.h>

#define NUMP 5

pthread_mutex_t fork_mutex[NUMP];
pthread_mutex_t help = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t attempt = PTHREAD_COND_INITIALIZER;
int count = 0;

int main()  
{
  int i;
  pthread_t diner_thread[NUMP]; 
  int dn[NUMP];
  void *diner();
  for (i=0;i<NUMP;i++)
    pthread_mutex_init(&fork_mutex[i], NULL);

  for (i=0;i<NUMP;i++){
    dn[i] = i;
    pthread_create(&diner_thread[i],NULL,diner,&dn[i]);
  }
  for (i=0;i<NUMP;i++)
    pthread_join(diner_thread[i],NULL);

  for (i=0;i<NUMP;i++)
    pthread_mutex_destroy(&fork_mutex[i]);
  
  pthread_exit(0);

}

void *diner(int *i)
{
  int v;
  int eating = 0;
  printf("I'm diner %d\n",*i);
  v = *i;
  while (eating < 5) {
	
    printf("%d is thinking\n", v);
    sleep( v/2);
    printf("%d is hungry\n", v); 
    pthread_mutex_lock(&help);
    while (count == 4) {
      pthread_cond_wait(&attempt, &help);
	}
    count++;
    pthread_mutex_unlock(&help);
    pthread_mutex_lock(&fork_mutex[v]);
    pthread_mutex_lock(&fork_mutex[(v+1)%NUMP]);
    printf("%d is eating\n", v);
    eating++;
    sleep(1);
    printf("%d is done eating\n", v);
    pthread_mutex_unlock(&fork_mutex[v]);
    pthread_mutex_unlock(&fork_mutex[(v+1)%NUMP]);
    pthread_mutex_lock(&help);
    count--;
    if (count <= 3){
      pthread_cond_signal(&attempt);
    }
    pthread_mutex_unlock(&help);
  
  }
  pthread_exit(NULL);
}
