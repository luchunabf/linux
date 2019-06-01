#include<unistd.h>
int main()
{
  char *const argv[] = { "ps", "-ef", NULL };
  char *const envp[] = { "PATH = /bin:usr/bin", "TERM = console", NULL};
  execl("/bin/ps", "ps", "-ef", NULL);

  //带P的，可以使用环境变量PATH，无需写全路径
  execlp("ps", "ps", "-ef", NULL);

  //带e的，需要自己组织环境变量
  execle("/bin/ps", "ps", "-ef", NULL);

  execv("/bin/ps", argv);

  //带p的，可以使用环境变量，无需写全路径
  execvp("ps", argv);

  //带e的，需要自己组织环境变量
  execve("/bin/ps", argv, envp);

  //后面的exec函数都会将前面的替换，故执行最后一次的函数命令
  return 0;
}
