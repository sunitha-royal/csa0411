#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_REQUESTS 100

int main() {
    int requests[MAX_REQUESTS], n, head, totalMovement = 0;

    // Input number of disk requests
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    // Input request queue
    printf("Enter disk request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    // Input initial head position
    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nServicing requests in FCFS order:\n");

    for (int i = 0; i < n; i++) {
        printf("Move from %d to %d\n", head, requests[i]);
        totalMovement += abs(requests[i] - head);
        head = requests[i];
    }

    printf("\nTotal head movement: %d cylinders\n", totalMovement);
    return 0;
}