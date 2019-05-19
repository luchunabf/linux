#include<stdio.h>
#include<string.h>
int my_strlen3(char* str)
{
 char *p = str;
 while(*str)
 {
  str++;
 }
 return (str - p);
}

int main()
{
 char* str = "abcdef";
 printf("%d\n",my_strlen3(str));
 return 0;
}
