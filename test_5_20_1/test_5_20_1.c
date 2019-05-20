#include<stdio.h>
#include<string.h>

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
int my_strlen2(char* str)
{
  if(*str == '\0')
    return 0;
  return (1 + my_strlen2(str + 1));
}
int my_strlen3(char* str)
{
  char* p = str;
  while(*str)
  {
    str++;
  }
  return (str - p);
}

int main()
{
  char* arr = "abcdefg";
  int ret1 = my_strlen1(arr);
  int ret2 = my_strlen2(arr);
  int ret3 = my_strlen3(arr);
  printf("%d\n", ret1);
  printf("%d\n", ret2);
  printf("%d\n", ret3);
  return 0;
}
