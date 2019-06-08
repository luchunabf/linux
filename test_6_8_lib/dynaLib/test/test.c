#include<stdio.h>
#include"add.h"
#include"sub.h"
#include"mul.h"
#include"div.h"

int main()
{
  int m = 12;
  int n = 2;
  int a = add(m,n);
  printf("m+n=%d\n",a);
  int b = sub(m,n);
  printf("m-n=%d\n",b);
  int c = mul(m,n);
  printf("m*n=%d\n",c);
  int d = div(m,n);
  printf("m/n=%d\n",d);
  return 0;
}
