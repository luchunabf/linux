#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex;
int ticket = 100;
void *yellow_bull(void *arg)
{
    while(1) {
        //pthread_mutex_lock( pthread_mutex_t *__mutex  )
        //  __mutex：   互斥锁变量
        //int pthread_mutex_trylock(pthread_mutex_t *mutex);
        //  非阻塞加锁：若现在不能加锁，则立即报错返回
        pthread_mutex_lock(&mutex);
        if (ticket > 0) {
            usleep(1000);
            printf("bull %d get a ticket:%d\n", (int)arg, ticket);
            ticket--;
            //int pthread_mutex_unlock(pthread_mutex_t *mutex);
            pthread_mutex_unlock(&mutex);
        }else {
            printf("have no tickets, bull %d exit\n", (int)arg);
            //用户在加锁之后，需要在任意有可能退出线程的地方进行解锁
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
    }
}
int main()
{
    pthread_t tid[4];

    //int pthread_mutex_init(pthread_mutex_t *mutex, 
    //  pthread_mutexattr_t *attr);
    //  mutex:  互斥锁变量
    //  attr：初始化互斥锁属性--通常置NULL
    pthread_mutex_init(&mutex, NULL);
    int i;
    for (i = 0; i < 4; i++) {
        int ret = pthread_create(&tid[i], NULL, yellow_bull, (void*)i);
        if (ret != 0) {
            printf("thread create error\n");
            return -1;
        }
    }
    for (i = 0; i < 4; i++) {
        pthread_join(tid[i], NULL);
    }
    //int pthread_mutex_destroy(pthread_mutex_t *mutex);
    //mutex:    互斥锁变量
    pthread_mutex_destroy(&mutex);
    return 0;
}
