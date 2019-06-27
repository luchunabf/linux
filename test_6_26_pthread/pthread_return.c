#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

void* thread (void* arg)
{
  int i = 0;
  for(;i < 5;++i)
  {
    sleep(1);
    printf("这是子线程\n");
  }
 return NULL;
}

int main()
{
  pthread_t tid;
  void* ret;
  
  void* p = pthread_self();
  printf("main tid:%X\n", p);

  pthread_create(&tid, NULL, thread, NULL);
  //sleep(3);
  //pthread_cancel(tid);
  
  pthread_exit(NULL);

  
  pthread_join(tid,&ret);

}
