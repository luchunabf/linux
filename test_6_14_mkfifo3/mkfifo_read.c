#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int main()
{
    umask(0);
    int ret = mkfifo("./test.fifo", 0664);
    if (ret < 0) {
        if (errno != EEXIST) {
            perror("mkfifo error");
            return -1;
        }
    }

    printf("start open -------\n");
    int fd = open("./test.fifo", O_RDONLY);
    printf("end open -------\n");
    if (fd < 0) {
        perror("open error");
        return -1;
    }
    printf("fifo:%s open success!!\n", "./test.fifo");

    while(1) {
        sleep(5);
        char buf[10] = {0};
        read(fd, buf, 9;
        printf("peer say: %s\n", buf);
    }
    close(fd);
    return 0;
}
