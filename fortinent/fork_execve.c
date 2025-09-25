#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/*

This example shows show fork and execve syscalls are being used to start 
new process, and also show the flexibility of having these two different 
syscalls, which allows to control the file descriptors in between.
*/
int main() {
    int pipefd[2];
    pid_t cpid1, cpid2;

    // Arguments for grep and sort
    char *grep_args[] = {"/bin/grep", "main", "input.txt", NULL};
    char *sort_args[] = {"/usr/bin/sort", NULL};

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    printf("pipefd0 %d\n", pipefd[0]);
    printf("pipefd1 %d\n", pipefd[1]);

    // First child - grep
    cpid1 = fork();
    if (cpid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid1 == 0) { // Child
        // Redirect stdout to pipe write end
	/*
	    This tells the newfd (which is 1 in this case 
of STDOUT) to refer to the same fd object that is pointed by oldfd
        */
        dup2(/*oldfd*/pipefd[1], /*newfd*/STDOUT_FILENO);

	/*
	We close the read end because this is the writer process
	*/
        close(pipefd[0]); // Close unused read end
	
	/*
	We close the write end because the STDOUT_FILENO is now 
	the handle of the write end of the pipe, so we don't need
	this second handle to the same fd object
	*/
        close(pipefd[1]);

        execve("/bin/grep", grep_args, NULL);
        perror("execve grep");
        exit(EXIT_FAILURE);
    }

    // Second child - sort
    cpid2 = fork();
    if (cpid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid2 == 0) { // Child
        // Redirect stdin to pipe read end
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]); // Close unused write end
        close(pipefd[0]);

        execve("/usr/bin/sort", sort_args, NULL);
        perror("execve sort");
        exit(EXIT_FAILURE);
    }

    // Parent closes both ends and waits
    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(cpid1, NULL, 0);
    waitpid(cpid2, NULL, 0);

    return 0;
}

