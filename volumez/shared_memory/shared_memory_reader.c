// reader.c
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
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    shared_data_t *data = mmap(NULL, sizeof(shared_data_t),
                               PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_t *sem_ready = sem_open(SEM_READY, 0);
    sem_t *sem_ack   = sem_open(SEM_ACK, 0);

    while (1) {
        sem_wait(sem_ready);   // Wait until writer says data is ready

        if (data->done) {
            break;
        }

        printf("[Reader] Received: %s\n", data->message);
	printf("[Reader] Press any key to continue...\n");
	getchar();
        sem_post(sem_ack);     // Tell writer it's OK to send next
    }

    printf("[Reader] All messages received.\n");

    munmap(data, sizeof(shared_data_t));
    close(shm_fd);
    sem_close(sem_ready);
    sem_close(sem_ack);

    // Clean up (only one process should do this!)
    shm_unlink(SHM_NAME);
    sem_unlink(SEM_READY);
    sem_unlink(SEM_ACK);

    return 0;
}

