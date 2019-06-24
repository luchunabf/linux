#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int x = 1;
int y = 1;

int sum(int* a, int* b)
{
  (*a)++;
  sleep(5);
  (*b)++;
  return (*a + *b);
}

void sigcb(int signo)
{
  printf("signal-------%d\n",sum(&x,&y));
}
int main()
{
  signal(SIGINT, sigcb);
  printf("main-------%d\n",sum(&x,&y));
  return 0;
}
