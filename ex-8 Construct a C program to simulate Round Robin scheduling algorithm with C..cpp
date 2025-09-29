#include <stdio.h>

struct Process {
    int id;
    int burst;
    int remaining;
    int arrival;
    int completion;
    int turnaround;
    int waiting;
};

int main() {
    int n, quantum, time = 0, completed = 0;
    struct Process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Input burst and arrival times
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time for Process %d: ", p[i].id);
        scanf("%d", &p[i].arrival);
        printf("Enter burst time for Process %d: ", p[i].id);
        scanf("%d", &p[i].burst);
        p[i].remaining = p[i].burst;
    }

    int queue[100], front = 0, rear = 0;
    int visited[20] = {0};

    // Enqueue first arrived processes
    for (int i = 0; i < n; i++) {
        if (p[i].arrival == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {
            time++;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && p[i].arrival <= time) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if (p[idx].remaining > quantum) {
            p[idx].remaining -= quantum;
            time += quantum;
        } else {
            time += p[idx].remaining;
            p[idx].remaining = 0;
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            completed++;
        }

        // Enqueue newly arrived processes
        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].arrival <= time) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // Re-enqueue current process if it's not finished
        if (p[idx].remaining > 0) {
            queue[rear++] = idx;
        }
    }

    // Display results
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
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