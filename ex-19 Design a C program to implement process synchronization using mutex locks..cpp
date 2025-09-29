#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5 // buffer size

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty;  // counts empty slots
sem_t full;   // counts filled slots
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100; // produce item

        sem_wait(&empty);             // wait for empty slot
        pthread_mutex_lock(&mutex);   // enter critical section

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex); // exit critical section
        sem_post(&full);              // signal full slot

        sleep(1); // simulate time
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);              // wait for full slot
        pthread_mutex_lock(&mutex);   // enter critical section

        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex); // exit critical section
        sem_post(&empty);             // signal empty slot

        sleep(2); // simulate time
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE); // initialize empty slots
    sem_init(&full, 0, 0);     // initialize full slots
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}