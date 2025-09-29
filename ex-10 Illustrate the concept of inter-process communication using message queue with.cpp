#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate unique key
    key = ftok("msgfile", 65);

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process: Sender
        message.msg_type = 1;
        strcpy(message.msg_text, "Hello from child process!");

        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        printf("Child sent message: %s\n", message.msg_text);
    } else {
        // Parent process: Receiver
        sleep(1); // Ensure child sends first
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        printf("Parent received message: %s\n", message.msg_text);

        // Cleanup
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}