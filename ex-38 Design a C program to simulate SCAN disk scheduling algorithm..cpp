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
    int requests[MAX_REQUESTS], n, head, diskSize, direction;
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

    printf("Enter direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

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

    printf("\nServicing order (SCAN):\n");

    if (direction == 1) { // Moving right
        for (int i = index; i < n; i++) {
            printf("Move to %d\n", requests[i]);
            totalMovement += abs(head - requests[i]);
            head = requests[i];
        }
        if (head != diskSize - 1) {
            totalMovement += abs(head - (diskSize - 1));
            head = diskSize - 1;
        }
        for (int i = index - 1; i >= 0; i--) {
            printf("Move to %d\n", requests[i]);
            totalMovement += abs(head - requests[i]);
            head = requests[i];
        }
    } else { // Moving left
        for (int i = index; i >= 0; i--) {
            printf("Move to %d\n", requests[i]);
            totalMovement += abs(head - requests[i]);
            head = requests[i];
        }
        if (head != 0) {
            totalMovement += abs(head - 0);
            head = 0;
        }
        for (int i = index + 1; i < n; i++) {
            printf("Move to %d\n", requests[i]);
            totalMovement += abs(head - requests[i]);
            head = requests[i];
        }
    }

    printf("\nTotal head movement: %d cylinders\n", totalMovement);
    return 0;
}