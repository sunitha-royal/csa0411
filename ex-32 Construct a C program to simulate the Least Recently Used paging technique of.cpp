#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES], usage[MAX_FRAMES];
    int pageCount, frameCount;
    int i, j, k, pageFaults = 0, time = 0;
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

    // Initialize frames and usage
    for (i = 0; i < frameCount; i++) {
        frames[i] = -1;
        usage[i] = 0;
    }

    printf("\nPage Replacement Process (LRU):\n");

    for (i = 0; i < pageCount; i++) {
        found = 0;

        // Check if page is already in frame
        for (j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                usage[j] = time++; // Update usage time
                break;
            }
        }

        if (!found) {
            // Page fault occurred
            pos = 0;
            for (j = 1; j < frameCount; j++) {
                if (usage[j] < usage[pos])
                    pos = j;
            }

            frames[pos] = pages[i];
            usage[pos] = time++;
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