// fifo_example_writer.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

/*
note that
1. this is actually a pipe same as unnamed pipe

2. you can find the pipe here:
yacovs@MOE-KT-6565923:~/interviews/volumez/named_pipe$ ls -l /tmp/myfifo
prw-r--r-- 1 yacovs yacovs 0 Sep 21 14:48 /tmp/myfifo

3. if not calling the mkfifo command the open() syscall with faill with:
Error opening FIFO: No such file or directory

*/
int main() {
    const char *fifo = "/tmp/myfifo";
    mkfifo(fifo, 0666); // create fifo in the above path

    /*
	This open() syscall is blocking until there is another process 
that reads from the fifo.
    */
    int fd = open(fifo, O_WRONLY); // tries to open the fifo in the path

    if (fd == -1) {
        // Print error to stderr with explanation
        perror("Error opening FIFO");
        // Or alternatively:
        fprintf(stderr, "Error opening FIFO: %s\n", strerror(errno));
        return -1;  // Or handle the error appropriately
    }
    const char *msg = "Hello from writer!";
    write(fd, msg, strlen(msg) + 1);
    close(fd);
    return 0;
}

