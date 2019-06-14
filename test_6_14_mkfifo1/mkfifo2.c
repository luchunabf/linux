#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>


#define ERR_EXIT(m) \
do \
{ \
  perror(m); \
  exit(EXIT_FAILURE); \
}while(0);


int main()
{
  umask(0);

  int outfd;
  outfd = open("abc.bak",O_WRONLY|O_CREAT|O_TRUNC,0664);
  if(outfd == -1)
    ERR_EXIT("open");

  int infd;
  infd = open("tp",O_RDONLY);
  if(infd == -1)
    ERR_EXIT("open");


  char buf[1024];
  int n;
  while((n =read(infd,buf,1024))>0)
  {
    write(outfd,buf,n);
  }
  
  close(infd);
  close(outfd);
  unlink("tp");
  return 0;
}

