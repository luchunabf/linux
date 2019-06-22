#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcb(int signo)//这里sigcb函数中的参数signo就表示的是传入（或接受到的）信号的编号
{
  printf("receive a signo:%d\n",signo);
  signal(signo, SIG_DFL);
}

int main()
{
  //signal
  //signal:修改信号的处理动作
  //signal(SIGINT, SIG_IGN);//将ctrl+c命令信号的默认处理动作修改为忽略
  //signal(SIGINT, sigcb);//signcb是自定义的函数名，故此时第二个参数传参传的是函数指针
  
  //sigaction
  //作用和signal相同，都是修改信号的处理动作
  //int sigaction(int signum, const struct sigaction* new_act, struct sigaction* old_act);
  struct sigaction new_act,old_act;
  new_act.sa_flags = 0;
  new_act.sa_handler = sigcb;

  //清空set信号集合
  sigemptyset(&new_act.sa_mask);//注意参数要取地址

  //修改
  sigaction(2,&new_act,&old_act);//用自定义的函数sigcb去修改2号信号默认的处理动作并保存于old_act中
                                //注意参数要取地址




  while(1)
  {
    printf("world~~~\n");
    sleep(1);
  }
  return 0;
}
