#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
using namespace std;

#define MAX_QUEUE 10
class BlockQueue
{
public:
  BlockQueue(int cap = MAX_QUEUE )//构造函数中将一个锁和两个条件变量（生产者条件变量，消费者条件变量）初始化
    :_capacity(cap)//cap用来限制阻塞管道的最大容量
  {
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&pro_cond,NULL);
    pthread_cond_init(&con_cond,NULL);
  }
  ~BlockQueue()//析构函数中将一个锁和两个条件变量（生产者条件变量，消费者条件变量）销毁
  {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&pro_cond);
    pthread_cond_destroy(&con_cond);
  }
  bool BlockQueuePush(int data)////将此函数所传形参data，推进队列中保存，传值即可(注意函数返回类型是bool)
  {
    pthread_mutex_lock(&mutex);//（要操作队列前）先加锁
    while(_queue.size() == _capacity)//////////循环判断队列是否放满//单线程可以用if，但是多线程的话必须用while
          //当多个线程各自先后拿到锁了以后，判断条件变量的条件均不满足，所以先后等待在条件变量的阻塞队列(pthread_cond_wait(&pro_cond,&mutex))上
          //然后当接收到唤醒信号后，所有等待在条件变量等待队列上的线程被唤醒，去竞争锁
          //先拿到锁的线程，已经默认（收到信号了）条件成立去执行后面的操作
          //而后拿到锁的线程因为是if所以没有（返回）进行条件变量的判断，而直接去（像前一个线程一样收到信号）执行默认的条件变量满足操作
          //而此刻条件变量的条件有可能不再满足，导致逻辑混乱
          //
          //[总结：多个线程都都等待在(pthread_cond_wait(&pro_cond,&mutex))这一步，
          //然后接收到条件满足的信号被同时唤醒，然后去竞争锁，先竞争到锁的直接执行满足条件的操作，
          //而后拿到锁的不能直接向先拿到锁的一样直接去执行信号唤醒后的操作，
          //应先返回判断条件处再次进行判断条件是否满足]
    {
    pthread_cond_signal(&con_cond);//当阻塞队列放满了以后，给消费者发送信号
      pthread_cond_wait(&pro_cond,&mutex);//注意牢记条件变量等待时需要互斥锁的保护：解锁+等待（前两部需要保持原子性）+加锁
    }
    _queue.push(data);//将data放入到阻塞队列中
    //pthread_cond_signal(&con_cond);//也可以在这里给消费者发送信号，这样的话队列放不满，也不会触发条件变量的阻塞等待
    pthread_mutex_unlock(&mutex);//操作完队列解锁
  }
  bool BlockQueuePop(int& data)//传引用，记牢：是要给所传的data地址中赋值，需传引用，否则出了函数，栈地址自动释放
  {
    pthread_mutex_lock(&mutex);//（要操作队列前）先加锁
    while(_queue.empty())//循环判断队列是否为空
    {
    pthread_cond_signal(&pro_cond);//当队列空的时候给生产者发送信号，让生产者生产
      pthread_cond_wait(&con_cond,&mutex);//注意牢记条件变量等待时需要互斥锁的保护：解锁+等待（前两部需要保持原子性）+加锁
    }
    data = _queue.front();//将阻塞队列队头元素给data赋值
    _queue.pop();//赋值后删除队头元素
    //pthread_cond_signal(&pro_cond);//也可以在这里给消费者发送信号，这样的话队列放不满，也不会触发条件变量的阻塞等待
    pthread_mutex_unlock(&mutex);//操作完队列解锁
  }
private:
  queue<int> _queue;//借助阻塞队列（一个场所）来实现生产者消费者模型
  int _capacity;//限制阻塞队列的最大容量
  pthread_mutex_t mutex;//一个锁保护共享区和条件等待（线程安全 是通过 互斥+同步 来实现）
  pthread_cond_t pro_cond;//生产者等待在生产者的条件等待（队列）上，所以生产者有生产者的条件变量
  pthread_cond_t con_cond;//消费者等待在消费者的条件等待（队列）上，所以消费者有消费者的条件变量
};

void* pro_thread(void* arg)
{
  BlockQueue* q = (BlockQueue*) arg;//因为参数是任意类型，故将参数强转为类类型
  int i = 0;//因为要把i放进队列中，i需要一直变，所以在循环外定义i并初始化
  while(1)
  {
    q->BlockQueuePush(i);//调用类类型中的生产者函数来把i放/推进阻塞队列中
    cout << "productor: "<< pthread_self()<<" put data: " << i << endl;//打印一下调用线程id和所放元素i的信息
    i++;//i自增（这一步可自定义为用户想给阻塞队列中放的值）
    //sleep(1);
  }
  return NULL;
}
void* con_thread(void* arg)
{
  BlockQueue* q = (BlockQueue*) arg;
  while(1)
  {
    int data;///////////////////////这里需要给data这块地址中赋值i，故每次进来循环后需要换一块地址，故再循环内部定义data
    q->BlockQueuePop(data);//调用类类型中的消费者函数来将队头元素赋值给data的地址中保存
    cout << "consumer: " << pthread_self() << " get data: " << data  << endl;
    //sleep(1);
  }
  return NULL;
}

/*
int main()
{
  //定义线程
  pthread_t pro_tid,con_tid;//定义两个线程，也可定义多个线程
  //生成类的对象
  BlockQueue q;//将我们定义的阻塞队列类实例化：生成对象
  //创建线程
  int ret = 0;
  if(ret = pthread_create(&pro_tid,NULL,pro_thread,(void*)&q) != 0)//创建生产者线程
  {
    cout << "productor thread create error" << endl;
    return -1;
  }

  if(ret = pthread_create(&con_tid,NULL,con_thread,(void*)&q) != 0)//创建消费者线程
  {
    cout << "consumer thread create error" << endl;
    return -1;
  }
  //线程等待
  pthread_join(pro_tid,NULL);//线程等待：等待生产者线程退出并释放内存
  pthread_join(con_tid,NULL);//线程等待：等待消费者线程退出并释放内存
  return 0;
}
*/ 


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

