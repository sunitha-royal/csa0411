#include <stdio.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int priority;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
};

int main() {
    int n, time = 0, completed = 0;
    struct Process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time for Process %d: ", p[i].id);
        scanf("%d", &p[i].arrival);
        printf("Enter burst time for Process %d: ", p[i].id);
        scanf("%d", &p[i].burst);
        printf("Enter priority for Process %d (lower number = higher priority): ", p[i].id);
        scanf("%d", &p[i].priority);
        p[i].remaining = p[i].burst;
    }

    while (completed < n) {
        int idx = -1;
        int highest_priority = 9999;

        // Select process with highest priority among arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].priority < highest_priority) {
                highest_priority = p[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].remaining--;
            time++;

            if (p[idx].remaining == 0) {
                completed++;
                p[idx].completion = time;
                p[idx].turnaround = p[idx].completion - p[idx].arrival;
                p[idx].waiting = p[idx].turnaround - p[idx].burst;
            }
        } else {
            time++; // Idle time
        }
    }

    // Display results
    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].priority, p[i].waiting, p[i].turnaround);
    }

    // Calculate averages
    float avg_wait = 0, avg_turn = 0;
    for (int i = 0; i < n; i++) {
        avg_wait += p[i].waiting;
        avg_turn += p[i].turnaround;
    }

    printf("\nAverage Waiting Time: %.2f", avg_wait / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turn / n);

    return 0;
}