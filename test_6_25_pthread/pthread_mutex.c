#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex;
int ticket = 100;

void yellow_bull(void* arg)
{
  int id = (int)arg;
  while(1)
  {
    pthread_mutex_lock(&mutex);
    if(ticket > 0)
    {
      usleep(1000);
      printf("bull %d get a ticket:%d\n",id,ticket);
      ticket--;
    }
    else 
    {
      printf("have no tickets, bull %d exit\n", id);
      pthread_mutex_unlock(&mutex);
      pthread_exit(NULL);
    }
    pthread_mutex_unlock(&mutex);
  }
}

int main()
{
  pthread_t tid[4];

  pthread_mutex_init(&mutex,NULL);
  int i;
  for(i = 0; i < 4; ++i)
  {
    int ret = pthread_create(&tid[i],NULL, yellow_bull, (void*)i);
    if(ret != 0)
    {
      printf("thread create error\n");
      return -1;
    }
  }
  for(i = 0; i < 4; ++i)
  {
    pthread_join(tid[i],NULL);
  }

  pthread_mutex_destroy(&mutex);
  return 0;
}


