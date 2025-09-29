#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key = ftok("shmfile", 65); // Generate unique key
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // Create shared memory
    char *str = (char *) shmat(shmid, NULL, 0); // Attach

    printf("Writing to shared memory...\n");
    strcpy(str, "Hello from shared memory!");

    shmdt(str); // Detach
    return 0;
}