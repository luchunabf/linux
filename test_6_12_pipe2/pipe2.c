#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<wait.h>
#include<stdlib.h>

int main()
{
  int testpipe[2];
  int ret;
  char buf[1024];
  const char* testbuf = "主程序发送的数据";
  if(pipe(testpipe)==0)
  {
    if(fork()==0)
    {
      ret = read(testpipe[0],buf,1023);
      buf[ret] = 0;
      printf("子程序读到的数据：%s",buf);
      close(testpipe[0]);
    }
    else 
    {
      ret = write(testpipe[1],testbuf,strlen(buf));
      ret = wait(NULL);
      close(testpipe[1]);
    }
  }
  return 0;
}
