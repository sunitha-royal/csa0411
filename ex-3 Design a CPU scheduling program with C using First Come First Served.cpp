#include <stdio.h>

int main() {
    int n, i;
    int burst_time[20], waiting_time[20], turnaround_time[20];
    int total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input burst times
    for (i = 0; i < n; i++) {
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    // First process has 0 waiting time
    waiting_time[0] = 0;

    // Calculate waiting time for each process
    for (i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
    }

    // Calculate turnaround time and total times
    for (i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + burst_time[i];
        total_wt += waiting_time[i];
        total_tat += turnaround_time[i];
    }

    // Display results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);

    return 0;
}