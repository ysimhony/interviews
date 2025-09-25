// pipe_example.c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/*
note 
1. that it is *impossible* to communicate between two processes
that are not parent-child using unnamed pipe
2. for bidirectional communication between two processes you will
need two pipe syscall
3. the first fd in the pipefd array is for the read and the second
fd in the array is for the write
*/
int main() {
    int pipefd[2];

    // int pipe(int pipefd[2]);
    pipe(pipefd);

    pid_t pid = fork();
    if (pid == 0) {
        // Child: read from pipe
        close(pipefd[1]);
        char buf[100];
        read(pipefd[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);
        close(pipefd[0]);
    } else {
        // Parent: write to pipe
        close(pipefd[0]);
        const char *msg = "Hello from parent!";
        write(pipefd[1], msg, strlen(msg) + 1);
        close(pipefd[1]);
        wait(NULL); // wait for the child process to finish
    }
    return 0;
}

