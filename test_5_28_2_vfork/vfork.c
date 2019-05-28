#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  //pid_t vfork(void);
  int pid = vfork();
  if (pid == 0) {
      printf("i am child!!\n");
      sleep(5);
      return -1;
      //exit(0);
      printf("i am child two!!\n");
          
  }
      printf("i am parent!!\n");
          return 0;
}
