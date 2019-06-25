#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void* root(void* arg)
{
  int i;
  for(;;)
  {
    printf("I am thread 1\n");
    sleep(1);
  }
}

int main(void)
{
  pthread_t tid;
  int ret;
  if((ret = pthread_create(&tid, NULL, root, NULL)) != 0)
  {
    fprintf(stderr, "pthread_create:%s\n",strerror(ret));
      exit(EXIT_FAILURE);
  }


  int i;
  for(;;)
  {
    printf("I am main pthread\n");
    sleep(1);
  }
}
