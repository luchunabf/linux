#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int hot_beef_noodle = 0;
int main()
{
    printf("---------------");
    sleep(3);
    // _exit(1);
    //exit(1);
    return 1;
    //char* ptr = NULL;
    //memcpy(ptr, "nihao", 5);
    printf("I want to eat hot beef noodle\n");
    if(hot_beef_noodle)
    {
      printf("eat hot beef noodle\n");
    }
    else 
    {
      printf("eat old noodle\n");
    }
    printf("want to eat noodle\n");
    return 0;
}
