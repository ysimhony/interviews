// fifo_example_reader.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h> 

int main() {
    const char *fifo = "/tmp/myfifo";
    char buf[100];

    int fd = open(fifo, O_RDONLY);
    read(fd, buf, sizeof(buf));
    printf("Reader got: %s\n", buf);
    close(fd);
    return 0;
}

