#include<stdio.h>
#include<string.h>

//strlen
int my_strlen1(char* str)
{
 int count = 0;
 while(*str)
 {
  count++;
  str++;
 }
 return count;
}

int main()
{
 char *str = "abcdef";
 printf("%d\n",my_strlen1(str));
 return 0;
}
