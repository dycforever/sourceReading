
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    pid_t pid = getpid();
    printf("%u", pid);
    getchar();

    int size = 1024 * 1024;
    char* mem = malloc(size);
    memset(mem, 0, size);

    int fd = open("testfile", O_RDWR | O_CREAT, 0666);
    write(fd, mem, size);
    fsync(fd);
    close(fd);
}