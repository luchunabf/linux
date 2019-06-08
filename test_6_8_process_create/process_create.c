#include<stdio.h>
#include<unistd.h>
#include<wait.h>
#include<stdlib.h>

typedef void (*FUNC)(char*);

void* func(void* arg)
{
  char* str = (char*)arg;
  printf("%s,child pid is %d,father pid is %d\n",str,getpid(),getppid());
  sleep(5);
  return;
}

void process_create(pid_t* pid,void* func,char* arg)
{
  *pid = fork();
  if(*pid < 0)
  {
    perror("fork error\n");
    return;
  }
  else if(*pid == 0)
  {
    while(1)
    {  
    FUNC funct = (FUNC)func;
    (*funct)(arg);
    exit(0);
    }
  }
  else
  {
    pid_t id = waitpid(-1, NULL, 0);
    printf("wait child prosess successfully,child id is %d\n",id);
    return;
  }
  return;
}

int main()
{
  char* arg = "child is runing";
  pid_t pid;
  process_create(&pid, func, arg);
}

