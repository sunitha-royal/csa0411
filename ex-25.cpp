#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main() {
    int fd;
    char buffer[100];
    struct stat fileStat;

    // --- fcntl and lseek ---
    fd = open("sample.txt", O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // Write some data
    write(fd, "Hello, UNIX I/O!\n", 17);

    // Move file pointer to beginning
    lseek(fd, 0, SEEK_SET);

    // Read back the data
    read(fd, buffer, 17);
    buffer[17] = '\0';
    printf("Read from file: %s", buffer);

    // Get file descriptor flags
    int flags = fcntl(fd, F_GETFL);
    printf("File access mode: ");
    switch (flags & O_ACCMODE) {
        case O_RDONLY: printf("Read only\n"); break;
        case O_WRONLY: printf("Write only\n"); break;
        case O_RDWR:   printf("Read/Write\n"); break;
    }

    close(fd);

    // --- stat ---
    if (stat("sample.txt", &fileStat) < 0) {
        perror("stat");
        exit(1);
    }

    printf("\nFile Metadata (stat):\n");
    printf("Size: %ld bytes\n", fileStat.st_size);
    printf("Permissions: %o\n", fileStat.st_mode & 0777);
    printf("Last modified: %ld\n", fileStat.st_mtime);

    // --- opendir and readdir ---
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(1);
    }

    struct dirent *entry;
    printf("\nDirectory Contents:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}