#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

int findOptimal(int pages[], int frames[], int pageCount, int frameCount, int currentIndex) {
    int i, j, farthest = currentIndex, pos = -1;
    int found;

    for (i = 0; i < frameCount; i++) {
        found = 0;
        for (j = currentIndex + 1; j < pageCount; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                found = 1;
                break;
            }
        }
        if (!found) {
            return i; // Page not used again, best to replace
        }
    }

    return (pos == -1) ? 0 : pos;
}

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int pageCount, frameCount;
    int i, j, k, pageFaults = 0;
    int found, pos;

    // Input number of pages
    printf("Enter number of pages: ");
    scanf("%d", &pageCount);

    printf("Enter page reference string:\n");
    for (i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }

    // Input number of frames
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    // Initialize frames to -1 (empty)
    for (i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }

    printf("\nPage Replacement Process (Optimal):\n");

    for (i = 0; i < pageCount; i++) {
        found = 0;

        // Check if page is already in frame
        for (j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // Page fault occurred
            if (i < frameCount) {
                frames[i] = pages[i]; // Fill empty frames first
            } else {
                pos = findOptimal(pages, frames, pageCount, frameCount, i);
                frames[pos] = pages[i];
            }
            pageFaults++;

            // Print current frame state
            printf("Page %d => ", pages[i]);
            for (k = 0; k < frameCount; k++) {
                if (frames[k] != -1)
                    printf("%d ", frames[k]);
                else
                    printf("- ");
            }
            printf(" (Page Fault)\n");
        } else {
            // No page fault
            printf("Page %d => No change (Hit)\n", pages[i]);
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}