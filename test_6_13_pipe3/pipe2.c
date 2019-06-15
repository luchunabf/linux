#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 100

int child_work(int pfd,char *fname)//创建文件fname，并且从管道pfd读数据到该文件中去
{
    int n,fd;
    char buf[MAX];

    if((fd = open(fname,O_WRONLY | O_CREAT | O_TRUNC,0666)) < 0)
    {
        fprintf(stderr,"Fail to open %s : %s.\n",fname,strerror(errno));
        return -1;
    }

    while( n = read(pfd,buf,sizeof(buf)) )
    {
        write(fd,buf,n);
    }
    
    close(pfd);
    close(fd);

    return 0;
}

int father_work(int pfd,char *fname)//从fname文件中读取数据到管道pfd
{
    int fd,n;
    char buf[MAX];

    if((fd = open(fname,O_RDONLY)) < 0)//打开已经存在的fname文件
    {
        fprintf(stderr,"Fail to open %s : %s.\n",fname,strerror(errno));
        return -1;
    }

    while(n = read(fd,buf,sizeof(buf)))//从fname文件中读取数据到buf中
    {
        write(pfd,buf,n);
    }
    
    close(pfd);
    close(fd);

    return 0;
}

int main()
{
    int pid;
    int fd[2];

    /*if(argc < 2)
    {
        fprintf(stderr,"usage %s argv[1] argv[2].\n",argv[0]);
        exit(EXIT_FAILURE);
    }*/

    if(pipe(fd) < 0)
    {
        perror("Fail to pipe");
        exit(EXIT_FAILURE);
    }

    if((pid = fork()) < 0)
    {
        perror("Fail to fork");
        exit(EXIT_FAILURE);
    
    }else if(pid == 0){
        
        close(fd[1]);
        child_work(fd[0],"pipe_read");
    
    }else{
    
        close(fd[0]);
        father_work(fd[1],"pipe_write");
        wait(NULL);
    }

    exit(EXIT_SUCCESS);
}
