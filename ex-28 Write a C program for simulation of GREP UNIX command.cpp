#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    FILE *fp;
    char line[MAX_LINE];

    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }

    char *pattern = argv[1];
    char *filename = argv[2];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("Searching for \"%s\" in %s...\n\n", pattern, filename);

    int lineNum = 1;
    while (fgets(line, MAX_LINE, fp)) {
        if (strstr(line, pattern)) {
            printf("Line %d: %s", lineNum, line);
        }
        lineNum++;
    }

    fclose(fp);
    return 0;
}