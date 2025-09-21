#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_MSG_LEN 256

char message[MAX_MSG_LEN];
int message_ready = 0;

pthread_mutex_t lock;

// condition variable
// A condition variable lets a thread wait efficiently for a condition (some shared state) 
// to change, without busy-waiting, and in coordination with other threads. 
// This is done by making the thread to go to sleep and be notified upon 
// state change
pthread_cond_t cond;

// Thread 1: Message sender (producer)
void* sender_thread(void* arg) {
    const char* messages[] = {
        "Hello from sender!",
        "How are you?",
        "This is thread communication.",
        "Bye!"
    };

    for (int i = 0; i < 4; ++i) {
        sleep(1); // simulate some work

        pthread_mutex_lock(&lock);
        strncpy(message, messages[i], MAX_MSG_LEN);
        message_ready = 1;
        pthread_cond_signal(&cond);  // notify receiver
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

// Thread 2: Message receiver (consumer)
void* receiver_thread(void* arg) {
    for (int i = 0; i < 4; ++i) {
        pthread_mutex_lock(&lock);
        while (!message_ready) {
	    /*
		Note that this pthread_cond_wait() call is associated 
with the lock variable (2nd parameter). This call does two things
		1. release the lock
		2. make the thread to go to sleep

		once the pthread_cond_signal() is being called by the 
other thread, this wakes up this thread which tries to take the lock 
first.
		
	    */	
            pthread_cond_wait(&cond, &lock); // wait for message
        }

        printf("[Receiver] Got message: %s\n", message);
        message_ready = 0; // reset for next message
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main() {
    pthread_t sender, receiver;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&sender, NULL, sender_thread, NULL);
    pthread_create(&receiver, NULL, receiver_thread, NULL);

    pthread_join(sender, NULL);
    pthread_join(receiver, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}

