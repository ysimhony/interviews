// writer.c
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#define SHM_NAME "/my_shared_mem"
#define SEM_READY "/sem_data_ready"
#define SEM_ACK "/sem_read_done"
#define MAX_MSG_LEN 256

typedef struct {
    char message[MAX_MSG_LEN];
    int done;
} shared_data_t;

int main() {
    const char *messages[] = {
        "Message 1",
        "Message 2",
        "Message 3",
        "Message 4",
        "Message 5"
    };

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);

    /*
	The default size of the fd is 0. we need to set the 
	size to be 4096 bytes
    */
    ftruncate(shm_fd, sizeof(shared_data_t));

    /*
	Because we map the fd physical pages into the virtual memory of the two processes, 
	both processes see the changes immediatly.
    */
    shared_data_t *data = mmap(NULL, sizeof(shared_data_t),
                               PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_t *sem_ready = sem_open(SEM_READY, O_CREAT, 0666, 0);
    sem_t *sem_ack   = sem_open(SEM_ACK,   O_CREAT, 0666, 0);

    for (int i = 0; i < 5; ++i) {
        strncpy(data->message, messages[i], MAX_MSG_LEN);
        data->done = 0;

        printf("[Writer] Sent: %s\n", messages[i]);
        sem_post(sem_ready);     // Signal reader that data is ready
        sem_wait(sem_ack);       // Wait for reader to confirm it was read
    }

    // Final signal to tell reader we're done
    data->done = 1;
    sem_post(sem_ready);         // Let reader wake up and check the done flag

    printf("[Writer] All messages sent.\n");

    /*
	Memory un map.
	Opposite operation to the mmap()
    */ 
    munmap(data, sizeof(shared_data_t));
    close(shm_fd);
    sem_close(sem_ready);
    sem_close(sem_ack);

    return 0;
}

