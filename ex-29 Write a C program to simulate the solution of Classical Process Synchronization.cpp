#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // Number of philosophers

sem_t mutex;
sem_t chopstick[N];

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        // Hungry
        sem_wait(&mutex);
        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id + 1) % N]);
        printf("Philosopher %d is eating.\n", id);
        sem_post(&mutex);

        sleep(2); // Eating

        // Done eating
        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);
        printf("Philosopher %d finished eating and is thinking again.\n", id);
    }

    return NULL;
}

int main() {
    pthread_t thread_id[N];
    int philosopher_ids[N];

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    for (int i = 0; i < N; i++) {
        philosopher_ids[i] = i;
        pthread_create(&thread_id[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    return 0;
}