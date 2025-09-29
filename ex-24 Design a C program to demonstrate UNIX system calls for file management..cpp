#include <stdio.h>
#include <fcntl.h>      // for open()
#include <unistd.h>     // for read(), write(), close(), lseek()
#include <string.h>
#include <stdlib.h>

int main() {
    int fd;
    char buffer[100];
    ssize_t bytes;

    // Create or open a file
    fd = open("demo.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }
    printf("File opened successfully with descriptor %d\n", fd);

    // Write to the file
    const char *text = "Hello from UNIX system calls!\n";
    bytes = write(fd, text, strlen(text));
    printf("Wrote %zd bytes to file.\n", bytes);

    // Move file pointer to beginning
    lseek(fd, 0, SEEK_SET);

    // Read from the file
    bytes = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytes] = '\0'; // null-terminate
    printf("Read %zd bytes: %s", bytes, buffer);

    // Close the file
    close(fd);
    printf("File closed.\n");

    return 0;
}