#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

// Function for SRTF (Shortest Remaining Time First) Scheduling
void SRTF(int n, int arrival[], int burst[]) {
    int remaining[MAX_PROCESSES], waitingTime[MAX_PROCESSES] = {0}, turnaroundTime[MAX_PROCESSES] = {0};
    int complete = 0, currentTime = 0, minBurst = INT_MAX;
    int shortest = 0, finishTime;
    bool found = false;

    for (int i = 0; i < n; i++) {
        remaining[i] = burst[i];
    }

    printf("\nSRTF Scheduling:\n");
    while (complete != n) {
        found = false;
        minBurst = INT_MAX;

        // Find process with minimum remaining burst time at current time
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= currentTime && remaining[i] > 0 && remaining[i] < minBurst) {
                minBurst = remaining[i];
                shortest = i;
                found = true;
            }
        }

        if (!found) {
            currentTime++;
            continue;
        }

        // Process the selected process
        remaining[shortest]--;
        currentTime++;

        // If a process finishes
        if (remaining[shortest] == 0) {
            complete++;
            finishTime = currentTime;
            turnaroundTime[shortest] = finishTime - arrival[shortest];
            waitingTime[shortest] = turnaroundTime[shortest] - burst[shortest];
        }
    }

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival[i], burst[i], waitingTime[i], turnaroundTime[i]);
    }
}

// Function for Round Robin Scheduling
void RoundRobin(int n, int arrival[], int burst[], int quantum) {
    int remaining[MAX_PROCESSES], waitingTime[MAX_PROCESSES] = {0}, turnaroundTime[MAX_PROCESSES] = {0};
    int time = 0;

    for (int i = 0; i < n; i++) {
        remaining[i] = burst[i];
    }

    printf("\nRound Robin Scheduling:\n");
    bool done;
    do {
        done = true;

        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0 && arrival[i] <= time) {
                done = false;

                if (remaining[i] > quantum) {
                    time += quantum;
                    remaining[i] -= quantum;
                } else {
                    time += remaining[i];
                    waitingTime[i] = time - burst[i] - arrival[i];
                    remaining[i] = 0;
                }
                turnaroundTime[i] = waitingTime[i] + burst[i];
            }
        }
    } while (!done);

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival[i], burst[i], waitingTime[i], turnaroundTime[i]);
    }
}

// Main function to execute both scheduling algorithms
int main() {
    int n, quantum;
    int arrival[MAX_PROCESSES], burst[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the arrival time and burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &arrival[i]);
        printf("Burst Time: ");
        scanf("%d", &burst[i]);
    }

    // Execute SRTF scheduling
    SRTF(n, arrival, burst);

    // Get quantum time for Round Robin scheduling
    printf("\nEnter the time quantum for Round Robin: ");
    scanf("%d", &quantum);

    // Execute Round Robin scheduling
    RoundRobin(n, arrival, burst, quantum);

    return 0;
}
