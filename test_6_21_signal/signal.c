nclude <stdio.h>
#include <unistd.h>
#include <signal.h>

//替换可以设置为三种处理动作： SIG_DFL（默认处理动作）
//							   SIG_TGN（忽略处理动作）
//							   User Space: void sighandler(int signo);
//signal(signo, SIG_DFL);//将自定义处理动作（函数）恢复默认处理动作

void sigcb(int signo)
{
    printf("recv a signo:%d\n", signo);
    signal(signo, SIG_DFL);//将自定义处理动作（函数）恢复默认处理动作
}
int main()
{
    //signal(SIGINT, SIG_IGN);
	//signal(SIGINT, sigcb);//后面的参数是处理动作的替换
    struct sigaction new_act, old_act;
    new_act.sa_flags = 0;
    new_act.sa_handler = sigcb;
    //int sigemptyset(sigset_t *set);
    //清空set信号集合
    sigemptyset(&new_act.sa_mask);

    //sigaction:作用是用newact替换2号信号的处理动作，将原有动作保存到oldact中
    sigaction(2, &new_act, &old_act);//old_act里面一般情况下都保存的是默认的处理动作(SIG_DFL)
									 //每个信号有它自带的处理动作（默认），此时放于old_act中

    while(1) {
        printf("xiuxiyihui~~\n");
        sleep(10);
    }
    return 0;
}
