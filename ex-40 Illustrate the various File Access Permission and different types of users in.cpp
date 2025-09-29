#include <stdio.h>
#include <string.h>

#define READ  4
#define WRITE 2
#define EXEC  1

typedef struct {
    char filename[20];
    int ownerPerm;  // Owner permissions
    int groupPerm;  // Group permissions
    int otherPerm;  // Others permissions
} File;

typedef enum { OWNER, GROUP, OTHER } UserType;

void checkPermission(File file, UserType user, int action) {
    int perm;
    switch (user) {
        case OWNER: perm = file.ownerPerm; break;
        case GROUP: perm = file.groupPerm; break;
        case OTHER: perm = file.otherPerm; break;
    }

    if ((perm & action) == action) {
        printf("Permission granted.\n");
    } else {
        printf("Permission denied.\n");
    }
}

int main() {
    File myFile;
    strcpy(myFile.filename, "report.txt");
    myFile.ownerPerm = READ | WRITE | EXEC;  // 7
    myFile.groupPerm = READ | EXEC;          // 5
    myFile.otherPerm = READ;                 // 4

    printf("File: %s\n", myFile.filename);
    printf("Owner permissions: %d\n", myFile.ownerPerm);
    printf("Group permissions: %d\n", myFile.groupPerm);
    printf("Others permissions: %d\n", myFile.otherPerm);

    printf("\nOwner tries to WRITE:\n");
    checkPermission(myFile, OWNER, WRITE);

    printf("\nGroup tries to WRITE:\n");
    checkPermission(myFile, GROUP, WRITE);

    printf("\nOthers try to EXECUTE:\n");
    checkPermission(myFile, OTHER, EXEC);

    return 0;
}