#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>

int main()
{
  umask(0);//mode_t umask(mode_t mask);
           //将当前进程的文件创建权限掩码修改成为mask
           
  //open接口:int open(const char *pathname, int flags, mode_t mode);
  int fd = open("./open.txt", O_RDWR|O_APPEND|O_CREAT|O_TRUNC,0664);
  if(fd < 0)
  {
    perror("open error");
    return -1;
  }

  //write接口：ssize_t write(int fd, const void *buf, size_t count);
  //  fd: open打开文件所返回的文件描述符
  //  buf：   要写入的数据
  //  count： 要写入的字节数
  // 返回值：实际写入的字节数    失败：-1
  char* buf = "I love you\n";
  ssize_t ret = write(fd, buf, strlen(buf));
  if(ret < 0)
  {
    perror("write error");
    return -1;
  }
  
  //lseek接口：off_t lseek(int fd, off_t offset, int whence);
  //跳转fd文件的读写位置到指定处
  //  whence：    SEEK_SET    SEEK_CUR    SEEK_END
  //  offset：    偏移量
  lseek(fd, 0 ,SEEK_SET);


  //read接口：ssize_t read(int fd, void *buf, size_t count);
  //从fd文件中读取count长度的数据，放到buf中
  //返回值：返回实际读取到的字节数    失败：-1
  char buf1[1024] = {0};
  ret = read(fd, buf1, 1023);
  if(ret < 0)
  {
    perror("read error");
    return -1;
  }
  printf("ret = %d-[%s]\n",ret , buf);

  //close接口：int close(int fd);
  close(fd);//open 必须和 close 搭配使用
}
