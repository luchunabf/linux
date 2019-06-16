#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<signal.h>
#include<errno.h>

//这个代码是 将管道(test.fifo)中的文件写入到新文件makefile2中去

int main()
{
  umask(0);
  //首先以可写方式创建并打开新文件makefile2
  int outfd;
  outfd = open("makefile2",O_WRONLY|O_CREAT|O_TRUNC,0664);
  if(outfd == -1)
  {
    perror("open error");
    exit(EXIT_FAILURE);
  }
  printf("create makefile2 success\n");

  //然后以可读方式打开管道
  int infd;
  infd = open("test.fifo",O_RDONLY);
  if(infd == -1)
  {
    perror("open error");
    exit(EXIT_FAILURE);
  }
  printf("open test.fifo success\n");

  //最后借助字符数组buf，将管道中的数据写入到makefile2文件中
  char buf[1024];
  int n;
  while((n = read(infd,buf,1023))>0)
  {
    write(outfd,buf,strlen(buf));
  }

  //关闭两个文件：makefile2文件 和 管道文件
  close(infd);
  close(outfd);

  unlink("test.fifo");
  return 0;
}
