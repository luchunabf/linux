#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int _noodles = 0;
pthread_mutex_t mutex;
pthread_cond_t eat_cond;
pthread_cond_t cook_cond;

void* eat_noodle(void* arg)
{
  while(1)
  {
  pthread_mutex_lock(&mutex);
  while(_noodles == 0)
  {
    //pthread_mutex_lock(&mutex);//我觉得可以在循环外加锁:就是在外面加锁
    pthread_cond_wait(&eat_cond,&mutex);

  }
  printf("eat noolde,delicious\n");
  _noodles = 0;//吃完面以后修改全局变量来是条件变量发生改变以满足厨师的唤醒
  pthread_cond_signal(&cook_cond);
  pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void* cook_noodle(void* arg)
{
  while(1)
  {
  pthread_mutex_lock(&mutex);
  while(_noodles == 1)
  {
    //pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cook_cond, &mutex);

  }
  printf("cook noodle,come on\n");
  _noodles = 1;
  pthread_cond_signal(&eat_cond);
  pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main()
{

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&eat_cond, NULL);
  pthread_cond_init(&cook_cond, NULL);

  pthread_t tid1,tid2;
  int i;
  for(i = 0; i < 4; ++i)
  {
    if((pthread_create(&tid1,NULL,eat_noodle,NULL)) != 0)
    {
      printf("pthread create error");
      return -1;
    }
  }

  for(i = 0; i < 4; ++i)
  {
    if((pthread_create(&tid2,NULL,cook_noodle,NULL)) != 0)
    {
      printf("pthread create error");
      return -1;
    }
  }

  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&eat_cond);
  pthread_cond_destroy(&cook_cond);

  return 0;

}
