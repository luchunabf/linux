#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* thread_run(void* arg)
{
  pthread_detach(pthread_self());
  printf("%s\n",(char*)arg);
  return NULL; 
}

int main(void)
{
  pthread_t tid;
  if(pthread_create(&tid,NULL,thread_run,"thread1 run...")!= 0)
  {
    printf("create thread error\n");
    return 1;
  }

  int ret = 0;
  sleep(1);
  
  if(pthread_join(tid,NULL) == 0)
  {
    printf("thread wait success\n");
    ret = 0;
  }
  else 
  {
    printf("thread wait failed\n");
    ret = 1;
  }
  return ret;

}
