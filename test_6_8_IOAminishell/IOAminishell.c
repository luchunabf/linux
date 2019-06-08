#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    while(1) {
        printf("[san@localhost]$ ");
        fflush(stdout);

        char tmp[1024] = {0};
        scanf("%[^\n]%*c", tmp);
        printf("[%s]\n", tmp);

        
        char *ptr = tmp;
        int argc = 0;
        char *argv[32] = {NULL};
        while(*ptr != '\0') {
            if (!isspace(*ptr)) {
                
                argv[argc] = ptr;
                argc++;
                while(!isspace(*ptr) && *ptr != '\0') ptr++;
                *ptr = '\0';
                ptr++;
                continue;
            }
            ptr++;
        }
																
        

        
        if (!strcmp(argv[0], "cd")) {
            
            chdir(argv[1]);
            continue;
        }

        int pid = fork();
		if(pid<0)
		{
			printf("fork error!");
			exit(0);
		}
        else if (pid == 0) {
			int i = 0;
			int flag=0;
			for(;argv[i]!=NULL;++i){
              if(strcmp(">",argv[i])==0){
              flag=1;
              break;
              }
          }
          int copyfd;
          argv[i]=NULL;
          if(flag)
          {
              if(argv[i+1]==NULL){
              printf("command error\n");
              exit(1);
              }
              close(1);
           int fd=open(argv[i+1],O_WRONLY | O_CREAT,0777);
           copyfd=dup2(1,fd);
          }
          execvp(argv[0],argv);
          if(flag){
              close(1);
              dup2(copyfd,1);
          }
            exit(0);
        }
        
        wait(NULL);
    }
    return 0;
}


