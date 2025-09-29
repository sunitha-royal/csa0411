#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int blockCount, processCount;
    int allocation[MAX_PROCESSES];

    printf("Enter number of memory blocks: ");
    scanf("%d", &blockCount);
    printf("Enter sizes of %d blocks:\n", blockCount);
    for (int i = 0; i < blockCount; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &processCount);
    printf("Enter sizes of %d processes:\n", processCount);
    for (int i = 0; i < processCount; i++) {
        scanf("%d", &processSize[i]);
        allocation[i] = -1; // initialize as not allocated
    }

    // Best Fit Allocation
    for (int i = 0; i < processCount; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blockCount; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    // Output Allocation Results
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processCount; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}