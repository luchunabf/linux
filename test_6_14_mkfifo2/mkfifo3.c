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
  mkfifo("tp",0664);

  int infd;
  infd = open("./abc",O_RDONLY);
  if(infd == -1)
    ERR_EXIT("open");

  int outfd;
  outfd = open("tp",O_WRONLY);
  if(outfd == -1)
    ERR_EXIT("open");

  char buf[1024];
  int n;
  while((n =read(infd,buf,1024))>0)
  {
    write(outfd,buf,n);
  }


  int outfd1;
  outfd1 = open("abc.bak",O_WRONLY|O_CREAT|O_TRUNC,0664);
  if(outfd1 == -1)
    ERR_EXIT("open");

  int infd1;
  infd1 = open("tp",O_RDONLY);
  if(infd1 == -1)
    ERR_EXIT("open");


  char buf1[1024];
  int n1;
  while((n1 =read(infd,buf,1024))>0)
  {
    write(outfd1,buf1,n1);
  }
  
  unlink("tp");
  
  close(infd);
  close(outfd);
  close(infd1);
  close(outfd1);
  return 0;
}

