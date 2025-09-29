#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Open source file for reading
    source_fd = open("source.txt", O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open destination file for writing (create if it doesn't exist)
    dest_fd = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        close(source_fd);
        exit(EXIT_FAILURE);
    }

    // Read from source and write to destination
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    // Close both files
    close(source_fd);
    close(dest_fd);

    printf("File copied successfully.\n");
    return 0;
}