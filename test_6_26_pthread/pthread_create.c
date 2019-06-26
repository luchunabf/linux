#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

void* thread(void* arg)
{
  int i;
  for(;;)
  {
    printf("I am thread 1~~~\n");
    sleep(1);
  }
  //return -1;
}

int main()
{
  pthread_t tid;


  int ret = pthread_create(&tid, NULL, thread, NULL);
  //pthread_join(tid,NULL);
  if(ret != 0)
  {
    printf("thread create error\n");
    exit(EXIT_FAILURE);
  }

  int i;
  for(;;)
  {
    printf("I am main thread~~~\n");
    sleep(1);
  }

  return 0;

}
