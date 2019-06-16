#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>

//这个代码是  将makefile文件里的数据写入到管道文件(test.fifo)中去
int main()
{

  //以只读的方式打开makefile文件
  int infd;
  infd = open("makefile",O_RDONLY);
  if(infd == -1)
  {
    perror("open error");
    exit(EXIT_FAILURE);
  }
  printf("open makefile success\n");

  //以只写的方式打开管道test.fifo
  int outfd;
  outfd = open("test.fifo",O_WRONLY);
  if(outfd == -1)
  {
    perror("open error");
    exit(EXIT_FAILURE);
  }
  printf("open test.fifo success\n");

  //通过字符数组buf，将文件makefile里的数据写入管道
  char buf[1024];
  int n;
  while((n = read(infd,buf,1023))>0)
  {
    write(outfd,buf,strlen(buf));
  }

  //最后别忘记关闭两个文件：makefile文件 和 管道文件
  close(infd);
  close(outfd);

  return 0;
}
