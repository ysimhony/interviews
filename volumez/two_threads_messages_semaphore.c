#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_MSG_LEN 256

char message[MAX_MSG_LEN];
sem_t sem_msg_ready; // sender → receiver
sem_t sem_msg_read;  // receiver → sender

void* sender_thread(void* arg) {
    const char* messages[] = {
        "Hello from sender!",
        "How are you?",
        "Semaphore communication.",
        "Bye!"
    };

    for (int i = 0; i < 4; ++i) {
        sem_wait(&sem_msg_read); // Wait for receiver to finish reading previous message

        strncpy(message, messages[i], MAX_MSG_LEN);
        sem_post(&sem_msg_ready);  // signal: new message ready
    }

    return NULL;
}

void* receiver_thread(void* arg) {
    for (int i = 0; i < 4; ++i) {
        sem_wait(&sem_msg_ready);  // wait for new message

        printf("[Receiver] Got message: %s\n", message);
        sem_post(&sem_msg_read);   // signal: message has been read
    }

    return NULL;
}

int main() {
    pthread_t sender, receiver;

    sem_init(&sem_msg_ready, /*pshared*/0, /*value*/0); // initially, no message is ready
    sem_init(&sem_msg_read, 0, 1);  // initially, receiver has "read" dummy message

    pthread_create(&sender, NULL, sender_thread, NULL);
    pthread_create(&receiver, NULL, receiver_thread, NULL);

    /*
	wait for both threads to finish but does not requires sender to 
	finish before the receiver
    */
    pthread_join(sender, NULL);
    pthread_join(receiver, NULL);

    sem_destroy(&sem_msg_ready);
    sem_destroy(&sem_msg_read);

    return 0;
}

