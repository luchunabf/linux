#include<stdio.h>
int check_sys()
{
 union Un
 {
  int i;
  char c;
 }un;
  un.i = 1;
 return un.c;
}

int main()
{
 int ret = check_sys();
 if(ret == 1)
  printf("该电脑是小端\n");
 else
 printf("该电脑是大端\n");
 return 0;
}
