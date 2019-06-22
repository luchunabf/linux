#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcb(int signo)
{
  printf("receive %d signal!\n",signo);
}

int main()
{
  signal(SIGINT, sigcb);
  signal(40,sigcb);

  sigset_t set, oldset;
  sigemptyset(&set);
  sigfillset(&set);
  sigprocmask(SIG_BLOCK, &set, &oldset);

  getchar();

  //sigprocmask(SIG_UNBLOCK,&set,NULL);
  sigprocmask(SIG_SETMASK,&oldset,NULL);


  return 0;
}
