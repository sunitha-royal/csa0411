#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define RECORD_SIZE 50

typedef struct {
    char data[RECORD_SIZE];
} Record;

typedef struct {
    Record records[MAX_RECORDS];
    int count;
} File;

void createFile(File* file) {
    int n;
    printf("Enter number of records to store: ");
    scanf("%d", &n);
    getchar(); // consume newline

    file->count = n;
    for (int i = 0; i < n; i++) {
        printf("Enter data for record %d: ", i + 1);
        fgets(file->records[i].data, RECORD_SIZE, stdin);
        file->records[i].data[strcspn(file->records[i].data, "\n")] = '\0'; // remove newline
    }

    printf("\nFile created with %d records.\n", n);
}

void readRecord(File* file, int index) {
    if (index < 0 || index >= file->count) {
        printf("Invalid record index.\n");
        return;
    }

    printf("\nReading record %d sequentially:\n", index + 1);
    for (int i = 0; i <= index; i++) {
        printf("Record %d: %s\n", i + 1, file->records[i].data);
    }
}

int main() {
    File myFile;
    int choice, index;

    while (1) {
        printf("\n--- Sequential File Allocation Menu ---\n");
        printf("1. Create File\n");
        printf("2. Read Record\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createFile(&myFile);
                break;
            case 2:
                printf("Enter record index to read (0-based): ");
                scanf("%d", &index);
                readRecord(&myFile, index);
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}