#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 100

typedef struct Block {
    int blockNumber;
    struct Block* next;
} Block;

typedef struct {
    char name[20];
    Block* start;
    Block* end;
} File;

int disk[MAX_BLOCKS]; // 0 = free, 1 = allocated

void initializeDisk() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        disk[i] = 0;
    }
}

int allocateBlock() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (disk[i] == 0) {
            disk[i] = 1;
            return i;
        }
    }
    return -1; // No free block
}

void createFile(File* file) {
    int n;
    printf("Enter file name: ");
    scanf("%s", file->name);

    printf("Enter number of blocks required: ");
    scanf("%d", &n);

    file->start = NULL;
    file->end = NULL;

    for (int i = 0; i < n; i++) {
        int blockNum = allocateBlock();
        if (blockNum == -1) {
            printf("Disk full. Could not allocate block %d.\n", i);
            break;
        }

        Block* newBlock = (Block*)malloc(sizeof(Block));
        newBlock->blockNumber = blockNum;
        newBlock->next = NULL;

        if (file->start == NULL) {
            file->start = newBlock;
            file->end = newBlock;
        } else {
            file->end->next = newBlock;
            file->end = newBlock;
        }
    }

    printf("File '%s' created with blocks: ", file->name);
    Block* temp = file->start;
    while (temp != NULL) {
        printf("%d -> ", temp->blockNumber);
        temp = temp->next;
    }
    printf("NULL\n");
}

void readFile(File* file) {
    printf("\nReading file '%s':\n", file->name);
    Block* temp = file->start;
    while (temp != NULL) {
        printf("Block %d\n", temp->blockNumber);
        temp = temp->next;
    }
}

int main() {
    File myFile;
    int choice;

    initializeDisk();

    while (1) {
        printf("\n--- Linked File Allocation Menu ---\n");
        printf("1. Create File\n");
        printf("2. Read File\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createFile(&myFile);
                break;
            case 2:
                readFile(&myFile);
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}