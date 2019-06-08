#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>

int main()
{
  while(1)
  {
    printf("[lc@localhost]$ ");
    fflush(stdout);

    char tmp[1024] = { 0 };
    scanf("%[^\n]%*c",tmp);
    printf("[%s]\n",tmp);

    char* ptr = tmp;
    int redirect_flag = 0;
    char* redirect_file = NULL;
    while(*ptr != '\0')
    {
      if(*ptr == '>')//清空重定向
      {
        *ptr = '\0';
        ptr++;
        redirect_flag = 1;
        if(*ptr == '>')//追加重定向
        {
          *ptr = '\0';
          ptr++;
          redirect_flag = 2;
        }
        while(isspace(*ptr) && *ptr != '\0')//将空格走完
          ptr++;
        redirect_file = ptr;//让redirect_file来标记重定向
        while(!isspace(*ptr) && *ptr != '\0')
          ptr++;
          *ptr = '\0';
      }
      ptr++;
    }
    
    ptr = tmp;
    int argc = 0;
    char* argv[32] = {NULL};
    while(*ptr != '\0')
    {
      if(!isspace(*ptr))
      {
        argv[argc] = ptr;
        argc++;
        while(!isspace(*ptr) && *ptr != '\0')
          ptr++;
        *ptr = '\0';
        ptr++;
        continue;
      }
      ptr++;
    }
    argv[argc] = NULL;

    if(!strcmp(argv[0],"cd"))//判断当前命令是否为内建命令
    {
      chdir(argv[1]);
      continue;
    }
    int pid = fork();
    if(pid < 0)
    {
      printf("fork error!");
      continue;
    }
    else if(pid == 0)
    {
      //ls浏览目录，实际上是将目录内容写入标准输出文件实现打印效果
      //标准输出重定向要做的就是把要写入到标准输出的数据/要打印的
      //数据不打印了（不写入到标准输出了）而是写入到新文件中
      int fd = 1;
      if(redirect_flag == 1)
        fd = open(redirect_file, O_CREAT|O_WRONLY|O_TRUNC, 0664);
      else if(redirect_flag == 2)
        fd = open(redirect_file, O_CREAT|O_WRONLY|O_APPEND, 0664);
      
      dup2(fd, 1);//标准输出重定向，将原本要写入标准输出1的数据写入新文件(fd)中
      execvp(argv[0], argv);
      //execvp函数程序替换成功则不返回任何值
      exit(0);//防止子进程程序替换失败
              //若子进程程序替换失败，则直接退出，因为终端不需要多个shell
    }
    //父进程，进程等待，防止僵尸进程
    wait(NULL);
  }
  return 0;
}

