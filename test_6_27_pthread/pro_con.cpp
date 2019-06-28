#include <iostream>
#include <queue>
#include <pthread.h>

#define MAX_CAP 10
class BlockQueue 
{
public:
  BlockQueue(int cap = MAX_CAP)
    :_capacity(cap)
  {
    pthread_mutex_init(&_mutex,NULL);
    pthread_cond_init(&_cond_con,NULL);
    pthread_cond_init(&_cond_pro,NULL);
  }

  ~BlockQueue()
  {
    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_cond_con);
    pthread_cond_destroy(&_cond_pro);
  }

  bool BlockQueuePush(int data)
  {
    pthread_mutex_lock(&_mutex);
    while(_queue.size() == _capacity)
    {
      pthread_cond_wait(&_cond_pro,&_mutex);
    }
    _queue.push(data);
    pthread_cond_signal(&_cond_con);
    pthread_mutex_unlock(&_mutex);
  }

  bool BlockQueuePop(int& data)
  {
    pthread_mutex_lock(&_mutex);
    while(_queue.empty())
    {
      pthread_cond_wait(&_cond_con,&_mutex);
    }
    data = _queue.front();
    _queue.pop();
    pthread_cond_signal(&_cond_pro);
    pthread_mutex_unlock(&_mutex);
  }


private:
  std::queue<int> _queue;
  int _capacity;
  pthread_mutex_t _mutex;
  pthread_cond_t _cond_pro; 
  pthread_cond_t _cond_con;
};

void* con_thread(void* arg)
{
  BlockQueue* q = (BlockQueue*)arg; 
  while(1)
  {
    int data;
    q->BlockQueuePop(data);//这一步用获得的i会给data赋值
    std::cout << "consumer: " << pthread_self() << " get data: " << data << "\n";
  }
  return NULL; 
}
void* pro_thread(void* arg)
{
  BlockQueue* q = (BlockQueue*)arg; 
  int i = 0;
  while(1)
  {
    q->BlockQueuePush(i++);
    std::cout << "productor: " << pthread_self() << " put data: " << i << "\n";
  }
  return NULL;
}

int main()
{
  BlockQueue q;
  pthread_t con_tid[4], pro_tid[4];
  int i, ret;
  for(i = 0; i < 4; ++i)
  {
    ret = pthread_create(&con_tid[i],NULL,con_thread,(void*)&q);
    if(ret != 0)
    {
      std::cout << "consumer thread create error\n";
      return -1;
    }
  }
  for(i = 0; i < 4; ++i)
  {
    ret = pthread_create(&pro_tid[i],NULL,pro_thread,(void*)&q);
    if(ret != 0)
    {
      std::cout << "consumer thread create error\n";
      return -1;
    }
  }

  for(i = 0; i < 4; ++i)
  {
    pthread_join(con_tid[i],NULL);
  }
  for(i = 0; i < 4; ++i)
  {
    pthread_join(pro_tid[i],NULL);
  }

  return 0;
}
