//#include<unistd.h>
//#include<string.h>
//#include<stdio.h>
//int main()
//{
// int i = 0;
// char bar[102];
// memset(bar, 0, sizeof(bar));
// const char* lable = "|/-\\";
// while(i <= 100)
// {
 // printf("[%-100s][%d%%][%c]\r", bar, i, lable[i%4]);
 // fflush(stdout);
 // bar[i++] = '#';
 // usleep(20000);
// }
// printf("\n");
// return 0;
//}
 #include <stdio.h>                                                          
 #include <unistd.h>
 #include <string.h>
 int main()
 {
   char bar[102];
   memset(bar , 0 ,sizeof(bar));
   int i = 0;
   const char* str = "-\\|/";
     while(i <= 100)
     {
    printf("\033[34;47m[%-100s] \033[31m[%d%%]\033[30m[%c]\r",bar,i,str[    i%4]);
    fflush(stdout);
    bar[i++] = '#';
    usleep(100000);
    }
  printf("\n");
  return 0;
 }
