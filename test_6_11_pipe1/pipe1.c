#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>

int main()
{
  int pipefd[2];
  int ret = pipe(pipefd);
  if(ret < 0)
  {
    perror("pipe error");
    return -1;
  }

  int pid = fork();
  if(pid == 0)
  {
    close(pipefd[0]);
    char buf[1024] = {0};
    //bint ret = read(pipefd[0],buf,1023);
    read(pipefd[0],buf,1023);
    //printf("child read buf:[%d-%s]\n", ret, buf);
    printf("child read buf:[%s]\n", buf);
    exit(0);
  }
  else if(pid > 0)
  {
    close(pipefd[0]);
    write(pipefd[1],"hello world",11);
    printf("---------line----------\n");
  }

  return 0;
}
