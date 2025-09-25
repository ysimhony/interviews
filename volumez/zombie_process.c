// zombie_example.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
A zombie process is a child process that has finished executing (i.e., exited), but whose exit status has not yet been read by its parent process via a wait() or waitpid() system call.

The zombie process remains in the process table:

As long as the parent is alive and has not reaped it.

Or until the parent exits, in which case the zombie is automatically reaped by the init process (PID 1).



The zombie processes can be seen with the defunct keyword:

yacovs@MOE-KT-6565923:~/interviews/volumez/shared_memory$ ps xf
    PID TTY      STAT   TIME COMMAND
    908 ?        Ss     0:00 ./wslconnect wsl -F -p 127.0.0.1:22004
    909 pts/4    Ss     0:00  \_ -bash
   1693 pts/4    R+     0:00      \_ ps xf
    569 pts/1    S+     0:00 -bash
    654 ?        Ss     0:00 ./wslconnect wsl -F -p 127.0.0.1:22003
    655 pts/2    Ss     0:00  \_ -bash
   1687 pts/2    S+     0:00      \_ ./zombie_process
   1688 pts/2    Z+     0:00          \_ [zombie_process] <defunct> <--
    545 ?        Ss     0:00 /usr/lib/systemd/systemd --user
    546 ?        S      0:00  \_ (sd-pam)

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

