#include <stdio.h>
#include <string.h>

#define MAX_FILES 100
#define NAME_LEN 30

struct File {
    char name[NAME_LEN];
};

int main() {
    struct File directory[MAX_FILES];
    int fileCount = 0;
    int choice;
    char filename[NAME_LEN];

    while (1) {
        printf("\n--- Single Level Directory ---\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. Display Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Create
                if (fileCount >= MAX_FILES) {
                    printf("Directory full!\n");
                    break;
                }
                printf("Enter file name to create: ");
                scanf("%s", filename);

                // Check for duplicates
                int exists = 0;
                for (int i = 0; i < fileCount; i++) {
                    if (strcmp(directory[i].name, filename) == 0) {
                        exists = 1;
                        break;
                    }
                }

                if (exists) {
                    printf("File already exists!\n");
                } else {
                    strcpy(directory[fileCount].name, filename);
                    fileCount++;
                    printf("File created successfully.\n");
                }
                break;

            case 2: // Delete
                printf("Enter file name to delete: ");
                scanf("%s", filename);
                int found = 0;
                for (int i = 0; i < fileCount; i++) {
                    if (strcmp(directory[i].name, filename) == 0) {
                        found = 1;
                        // Shift remaining files
                        for (int j = i; j < fileCount - 1; j++) {
                            strcpy(directory[j].name, directory[j + 1].name);
                        }
                        fileCount--;
                        printf("File deleted successfully.\n");
                        break;
                    }
                }
                if (!found) {
                    printf("File not found!\n");
                }
                break;

            case 3: // Search
                printf("Enter file name to search: ");
                scanf("%s", filename);
                found = 0;
                for (int i = 0; i < fileCount; i++) {
                    if (strcmp(directory[i].name, filename) == 0) {
                        found = 1;
                        printf("File found at position %d.\n", i + 1);
                        break;
                    }
                }
                if (!found) {
                    printf("File not found!\n");
                }
                break;

            case 4: // Display
                if (fileCount == 0) {
                    printf("Directory is empty.\n");
                } else {
                    printf("Files in directory:\n");
                    for (int i = 0; i < fileCount; i++) {
                        printf("%d. %s\n", i + 1, directory[i].name);
                    }
                }
                break;

            case 5: // Exit
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}