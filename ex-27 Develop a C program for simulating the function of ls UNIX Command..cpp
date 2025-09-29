#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd;
    char buffer[100];
    struct stat fileStat;

    // 1. Create and open file
    fd = open("myfile.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("Error creating file");
        exit(1);
    }
    printf("File created and opened successfully.\n");

    // 2. Write to file
    const char *text = "This is a sample file.\n";
    write(fd, text, strlen(text));
    printf("Data written to file.\n");

    // 3. Move file pointer to beginning
    lseek(fd, 0, SEEK_SET);

    // 4. Read from file
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytesRead] = '\0';
    printf("Data read from file:\n%s", buffer);

    // 5. Get file metadata
    if (stat("myfile.txt", &fileStat) == 0) {
        printf("\nFile Metadata:\n");
        printf("Size: %ld bytes\n", fileStat.st_size);
        printf("Permissions: %o\n", fileStat.st_mode & 0777);
        printf("Last modified: %ld\n", fileStat.st_mtime);
    } else {
        perror("stat");
    }

    // 6. Rename file
    if (rename("myfile.txt", "renamed_file.txt") == 0) {
        printf("File renamed successfully.\n");
    } else {
        perror("rename");
    }

    // 7. Delete file
    if (unlink("renamed_file.txt") == 0) {
        printf("File deleted successfully.\n");
    } else {
        perror("unlink");
    }

    close(fd);
    return 0;
}