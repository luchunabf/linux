#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
  pid_t pid;
  pid = fork();
  if(pid < 0)
  {
    printf("%s fork error\n",__FUNCTION__);
    return 1;
  }
  else if( pid == 0 )
  {
    printf("child is run,pid id : %d\n",getpid());
    sleep(5);
    exit(257);
  }
  else 
  {
    int status = 0;
    pid_t ret = waitpid(-1, &status, 0);//阻塞式等待
    printf("this is test for wait\n");
    if( WEXITED && ret == pid )
    {
      printf("wait child 5s success,child return code is:%d.\n",WEXITSTATUS(status));
    }
    else 
    {
      printf("wait child failed, return.\n");
      return 1;
    }
  }
  return 0;
}
