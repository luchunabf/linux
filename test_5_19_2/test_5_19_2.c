#include<stdio.h>
#include<string.h>
int my_strlen2(char* str)
{
 if(*str == '\0' )
    return 0;
 return (1 + my_strlen2(str + 1));
}

int main()
{
 char* str = "abcdef";
 printf("%d\n",my_strlen2(str));
 return 0;
}
