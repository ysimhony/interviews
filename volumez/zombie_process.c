// zombie_example.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
A zombie process is a child process that has finished executing (i.e., exited), but whose exit status has not yet been read by its parent process via a wait() or waitpid() system call.

The zombie process remains in the process table:

As long as the parent is alive and has not reaped it.

Or until the parent exits, in which case the zombie is automatically reaped by the init process (PID 1).
*/
int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("[Child] PID: %d — exiting immediately\n", getpid());
        exit(0);  // Child exits quickly
    } else {
        // Parent process
        printf("[Parent] PID: %d — sleeping for 60 seconds, not calling wait()\n", getpid());
        sleep(60);  // While parent sleeps, child becomes zombie
    }

    return 0;
}

