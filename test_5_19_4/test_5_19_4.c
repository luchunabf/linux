#include<stdio.h>
int check_sys()
{
 int i = 1;
 return  *(char*)(&i);
}

int main()
{
 int ret = check_sys();
 if(ret == 1)
    printf("该电脑是小端\n");
 else
    printf("改电脑是大端\n");
 return 0;
}
