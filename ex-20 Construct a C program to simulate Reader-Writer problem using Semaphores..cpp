#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;      // protects readCount
sem_t wrt;        // controls access to shared resource
int readCount = 0;
int sharedData = 0;

void* reader(void* arg) {
    int id = *((int*)arg);
    sem_wait(&mutex);
    readCount++;
    if (readCount == 1)
        sem_wait(&wrt); // first reader locks writer
    sem_post(&mutex);

    // Reading section
    printf("Reader %d reads sharedData = %d\n", id, sharedData);
    sleep(1);

    sem_wait(&mutex);
    readCount--;
    if (readCount == 0)
        sem_post(&wrt); // last reader unlocks writer
    sem_post(&mutex);
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    sem_wait(&wrt); // writer locks resource

    // Writing section
    sharedData += 10;
    printf("Writer %d updates sharedData to %d\n", id, sharedData);
    sleep(2);

    sem_post(&wrt); // writer unlocks resource
    return NULL;
}

int main() {
    pthread_t r[5], w[2];
    int rID[5] = {1, 2, 3, 4, 5};
    int wID[2] = {1, 2};

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader and writer threads
    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &wID[i]);
    for (int i = 0; i < 5; i++)
        pthread_create(&r[i], NULL, reader, &rID[i]);

    // Join threads
    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);
    for (int i = 0; i < 5; i++)
        pthread_join(r[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}