#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<errno.h>
#include<string.h>

int main(void)
{
  pid_t pid = fork();
  if(pid == -1)
  {
    perror("fork");
    exit(1);
  }
  else if(pid == 0)
  {
    sleep(20);
    exit(10);
  }
  else 
  {
    int status;
    int ret = wait(&status);
    if( ret > 0 && (status & 0x7f) == 0 )
    {  //正常退出 （返回status低16位中的高8位，此时低8位为0）
      printf("child exit code:%d\n", (status) >> 8 & 0xff);
    }
    else if(ret > 0) 
    {  //异常退出：终止信号（低8位）
      printf("sig code:%d\n", status & 0x7f);
    }
  }
}
