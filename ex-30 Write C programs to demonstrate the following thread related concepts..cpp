#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Thread function
void* threadFunction(void* arg) {
    int id = *((int*)arg);
    printf("Thread %d is running...\n", id);

    // Demonstrating pthread_exit
    char* message = malloc(30);
    sprintf(message, "Thread %d exited", id);
    pthread_exit((void*)message);
}

int main() {
    pthread_t tid1, tid2;
    int id1 = 1, id2 = 2;
    void* status1;
    void* status2;

    // (i) Create threads
    if (pthread_create(&tid1, NULL, threadFunction, &id1) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }
    if (pthread_create(&tid2, NULL, threadFunction, &id2) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }

    // (ii) Join threads
    pthread_join(tid1, &status1);
    pthread_join(tid2, &status2);

    printf("Thread 1 returned: %s\n", (char*)status1);
    printf("Thread 2 returned: %s\n", (char*)status2);

    free(status1);
    free(status2);

    // (iii) Check if threads are equal
    if (pthread_equal(tid1, tid2))
        printf("Threads are equal.\n");
    else
        printf("Threads are not equal.\n");

    return 0;
}