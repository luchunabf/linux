nclude <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcb(int signo) {
    printf("recv signo:%d\n", signo);
}
int main()
{
    signal(SIGINT, sigcb);
    signal(40, sigcb);
    //int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);//默认阻塞集合是block=mask，然后调用sigprocmask修改默认阻塞集合
	//当第一个参数是SIG_BLOCK时，向阻塞集合中加入set集合中的信号，block=mask|set    				oldset：保存修改前阻塞集合中的信号
	//当第一个参数是SIG_UNBLOCK时，从阻塞集合中移除set集合中的信号，block=mask&(~set)				oldset：保存修改前阻塞集合中的信号
	//当第一个参数是SIG_SETMASK时，向阻塞集合中加入set集合中的信号，block=set							oldset：保存修改前阻塞集合中的信号
    sigset_t set, oldset;
    sigemptyset(&set);
    //int sigfillset(sigset_t *set);//向set集合中添加所有信号
    
    //int sigaddset(sigset_t *set, int signum);//向set集合中添加signum信号
    
    sigfillset(&set);//向set集合中添加所有信号
    sigprocmask(SIG_BLOCK, &set, &oldset);//阻塞set中的信号，oldset：保存修改前阻塞集合中的信号

    getchar();//输入回车，对所有信号解除阻塞

    sigprocmask(SIG_UNBLOCK, &set, NULL);//从阻塞集合中移除set集合中的信号
    //sigprocmask(SIG_SETMASK, &oldset, NULL);
    return 0;
}

