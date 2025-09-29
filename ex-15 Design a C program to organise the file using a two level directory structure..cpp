#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FILES 20
#define NAME_LEN 30

struct File {
    char name[NAME_LEN];
};

struct Directory {
    char userName[NAME_LEN];
    struct File files[MAX_FILES];
    int fileCount;
};

int main() {
    struct Directory users[MAX_USERS];
    int userCount = 0;
    int choice;
    char userName[NAME_LEN], fileName[NAME_LEN];

    while (1) {
        printf("\n--- Two Level Directory ---\n");
        printf("1. Create User Directory\n");
        printf("2. Create File\n");
        printf("3. Delete File\n");
        printf("4. Search File\n");
        printf("5. Display User Files\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int i, j, found;

        switch (choice) {
            case 1: // Create User Directory
                if (userCount >= MAX_USERS) {
                    printf("Maximum user limit reached.\n");
                    break;
                }
                printf("Enter user name: ");
                scanf("%s", userName);

                // Check if user already exists
                found = 0;
                for (i = 0; i < userCount; i++) {
                    if (strcmp(users[i].userName, userName) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (found) {
                    printf("User already exists.\n");
                } else {
                    strcpy(users[userCount].userName, userName);
                    users[userCount].fileCount = 0;
                    userCount++;
                    printf("User directory created.\n");
                }
                break;

            case 2: // Create File
                printf("Enter user name: ");
                scanf("%s", userName);
                found = 0;
                for (i = 0; i < userCount; i++) {
                    if (strcmp(users[i].userName, userName) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("User not found.\n");
                    break;
                }

                if (users[i].fileCount >= MAX_FILES) {
                    printf("User directory full.\n");
                    break;
                }

                printf("Enter file name to create: ");
                scanf("%s", fileName);

                // Check for duplicate file
                for (j = 0; j < users[i].fileCount; j++) {
                    if (strcmp(users[i].files[j].name, fileName) == 0) {
                        printf("File already exists.\n");
                        break;
                    }
                }

                if (j == users[i].fileCount) {
                    strcpy(users[i].files[users[i].fileCount].name, fileName);
                    users[i].fileCount++;
                    printf("File created successfully.\n");
                }
                break;

            case 3: // Delete File
                printf("Enter user name: ");
                scanf("%s", userName);
                found = 0;
                for (i = 0; i < userCount; i++) {
                    if (strcmp(users[i].userName, userName) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("User not found.\n");
                    break;
                }

                printf("Enter file name to delete: ");
                scanf("%s", fileName);
                for (j = 0; j < users[i].fileCount; j++) {
                    if (strcmp(users[i].files[j].name, fileName) == 0) {
                        for (int k = j; k < users[i].fileCount - 1; k++) {
                            strcpy(users[i].files[k].name, users[i].files[k + 1].name);
                        }
                        users[i].fileCount--;
                        printf("File deleted successfully.\n");
                        break;
                    }
                }

                if (j == users[i].fileCount) {
                    printf("File not found.\n");
                }
                break;

            case 4: // Search File
                printf("Enter user name: ");
                scanf("%s", userName);
                found = 0;
                for (i = 0; i < userCount; i++) {
                    if (strcmp(users[i].userName, userName) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("User not found.\n");
                    break;
                }

                printf("Enter file name to search: ");
                scanf("%s", fileName);
                for (j = 0; j < users[i].fileCount; j++) {
                    if (strcmp(users[i].files[j].name, fileName) == 0) {
                        printf("File found at position %d.\n", j + 1);
                        break;
                    }
                }

                if (j == users[i].fileCount) {
                    printf("File not found.\n");
                }
                break;

            case 5: // Display User Files
                printf("Enter user name: ");
                scanf("%s", userName);
                found = 0;
                for (i = 0; i < userCount; i++) {
                    if (strcmp(users[i].userName, userName) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("User not found.\n");
                    break;
                }

                if (users[i].fileCount == 0) {
                    printf("No files in this directory.\n");
                } else {
                    printf("Files in %s's directory:\n", users[i].userName);
                    for (j = 0; j < users[i].fileCount; j++) {
                        printf("%d. %s\n", j + 1, users[i].files[j].name);
                    }
                }
                break;

            case 6:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}