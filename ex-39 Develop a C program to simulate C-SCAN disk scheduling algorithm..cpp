#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void sort(int arr[], int n) {
    // Simple bubble sort
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int main() {
    int requests[MAX_REQUESTS], n, head, diskSize;
    int totalMovement = 0;

    printf("Enter total number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size (max cylinder number): ");
    scanf("%d", &diskSize);

    // Add head to request list and sort
    requests[n++] = head;
    sort(requests, n);

    // Find head index
    int index;
    for (int i = 0; i < n; i++) {
        if (requests[i] == head) {
            index = i;
            break;
        }
    }

    printf("\nServicing order (C-SCAN):\n");

    // Move right from head to end
    for (int i = index; i < n; i++) {
        printf("Move to %d\n", requests[i]);
        totalMovement += abs(head - requests[i]);
        head = requests[i];
    }

    // Jump to beginning (cylinder 0)
    if (head != diskSize - 1) {
        totalMovement += abs(head - (diskSize - 1));
        head = 0;
        totalMovement += diskSize - 1;
        printf("Jump to 0 (no service)\n");
    }

    // Continue servicing from beginning to just before original head
    for (int i = 0; i < index; i++) {
        printf("Move to %d\n", requests[i]);
        totalMovement += abs(head - requests[i]);
        head = requests[i];
    }

    printf("\nTotal head movement: %d cylinders\n", totalMovement);
    return 0;
}