#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>

int main()
{
  //管道操作
  umask(0);
  int ret;
  ret = mkfifo("./test.fifo",0664);
  if(ret < 0)
  {
    perror("mkfifo error");
    exit(EXIT_FAILURE);
  }

  //管道文件操作
  int fd;
  printf("start open ----------\n");
  fd = open("./test.fifo",O_WRONLY,0664);
  printf("end open ----------\n");
  if(fd < 0)
  {
    perror("open error");
    exit(EXIT_FAILURE);
  }
  printf("./test.fifo open success\n");

  //管道写数据
  while(1)
  {
    char buf[10] = {0};
    printf("I say:");
    fflush(stdout);
    scanf("%s",buf);
    //write("./test.fifo",buf,strlen(buf));
    write(fd,buf,strlen(buf));
  }

  close(fd);
  
  return 0;
}
