#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100
#define MAX_FILE_BLOCKS 10

typedef struct {
    int indexBlock[MAX_FILE_BLOCKS]; // Pointers to data blocks
    int blockCount;                  // Number of blocks allocated
    char name[20];                   // File name
} File;

int memory[MAX_BLOCKS]; // 0 = free, 1 = allocated

void initializeMemory() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        memory[i] = 0;
    }
}

int allocateBlock() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (memory[i] == 0) {
            memory[i] = 1;
            return i;
        }
    }
    return -1; // No free block
}

void createFile(File* file) {
    printf("Enter file name: ");
    scanf("%s", file->name);

    printf("Enter number of blocks required: ");
    scanf("%d", &file->blockCount);

    if (file->blockCount > MAX_FILE_BLOCKS) {
        printf("Error: Exceeds maximum blocks per file.\n");
        return;
    }

    for (int i = 0; i < file->blockCount; i++) {
        int block = allocateBlock();
        if (block == -1) {
            printf("Memory full. Could not allocate block %d.\n", i);
            file->blockCount = i; // Adjust to actual allocated
            break;
        }
        file->indexBlock[i] = block;
    }

    printf("File '%s' created with blocks: ", file->name);
    for (int i = 0; i < file->blockCount; i++) {
        printf("%d ", file->indexBlock[i]);
    }
    printf("\n");
}

void readFile(File* file) {
    printf("\nReading file '%s' block-wise:\n", file->name);
    for (int i = 0; i < file->blockCount; i++) {
        printf("Block %d: Data at memory[%d]\n", i + 1, file->indexBlock[i]);
    }
}

int main() {
    File myFile;
    int choice;

    initializeMemory();

    while (1) {
        printf("\n--- Indexed File Allocation Menu ---\n");
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