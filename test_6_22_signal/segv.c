#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main()
{
  //kill
  //kill(getpid(),SIGKILL);//给该进程发送SIGKILL信号
  
  //raise
  //raise(SIGTERM);//向自己发送SIGTERM信号
  //raise(15);//向自己发送SIGTERM信号
  
  //abort
  //abort();//给自己发送SIGABRT异常终止信号
  
  //alarm(int seconds)  过second秒之后给自己发送SIGALRM终止当前进程信号
  //alarm(10);

  while(1)
  {
    printf("hello~~~\n");
    sleep(1);
  }


  return 0;
}
