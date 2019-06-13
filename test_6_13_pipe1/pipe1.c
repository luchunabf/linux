#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#define N 10
#define MAX 100

int child_read_pipe(int fd)
{
  char buf[N];
  int n = 0;
  while(1)
  {
    n = read(fd,buf,sizeof(buf));//sizeof(数组名)计算的是整个数组的大小
    buf[n] = '\0';

    printf("read %d bytes:%s.\n",n,buf);

    if(strncmp(buf,"quit",4)==0)
      break;
  }
return 0;
}


int parent_write_pipe(int fd)
{
 char buf[MAX] = {0};

 while(1)
 {
   printf(">");
   fgets(buf,sizeof(buf),stdin);
   buf[strlen(buf)-1] = '\0';//////////////////////////
   write(fd,buf,strlen(buf));
   usleep(500);

  if(strncmp(buf,"quit",4)==0)
    break;
 }
 return 0;
}


int main()
{
  int pid;
  int fd[2];

  if(pipe(fd)<0)
  {
    perror("Fail to pipe");
    exit(EXIT_FAILURE);
  }

  if((pid = fork())<0)
  {
    perror("Fail to fork");
    exit(EXIT_FAILURE);
  }
  else if(pid == 0)
  {
    close(fd[1]);
    child_read_pipe(fd[0]);
  }
  else 
  {
    close(fd[0]);
    parent_write_pipe(fd[1]);
  }
  exit(EXIT_SUCCESS);
}
