#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

int main()
{
  int fd[2];
  int count = 0;
  
  if(pipe(fd)<0)
  {
    perror("Fail to create pipe");
    exit(EXIT_FAILURE);
  }

  while(1)
  {
    write(fd[1],"a",sizeof(char));
    printf("count = %d.\n",++count);
  }
  return 0;
}
