#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>   // For struct user_regs_struct
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    pid_t child;
    int status;
    long syscall;
    struct user_regs_struct regs;

    child = fork();
    if (child == 0) {
        // Child process: let the parent trace us
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);

	/*
	The child process signals himself to stop
	*/
        kill(getpid(), SIGSTOP); // Pause so parent can attach
        execl("/bin/ls", "ls", NULL);
    } else {
        // Parent process: tracer
	/*
	This syscalls makes the parent process to block until the 
	child process changes its state
	*/
        waitpid(child, &status, 0); // Wait for SIGSTOP from child

	/*
	This makes the child process to continue its execution, but
	asks the child process to notify the parent process on every 
	entry/exit syscall in the child process
	*/
        ptrace(PTRACE_SYSCALL, child, NULL, NULL); // Let it continue

        while (1) {
            waitpid(child, &status, 0);
            if (WIFEXITED(status))
                break;

            // At syscall entry or exit
            ptrace(PTRACE_GETREGS, child, NULL, &regs);
#ifdef __x86_64__
            syscall = regs.orig_rax;
#else
            syscall = regs.orig_eax;  // For 32-bit systems
#endif
            printf("Syscall number: %ld\n", syscall);

            // Resume and wait for next syscall
            ptrace(PTRACE_SYSCALL, child, NULL, NULL);
        }
    }
    return 0;
}

