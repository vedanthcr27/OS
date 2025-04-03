#include <stdio.h>
#include <math.h>

#define MAX_PROCESSES 10

typedef struct {
    int id;
    int burst_time;
    int period;
    int remaining_time;
} Process;

void sort_by_period(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].period > processes[j + 1].period) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int calculate_lcm(Process processes[], int n) {
    int result = processes[0].period;
    for (int i = 1; i < n; i++) {
        result = lcm(result, processes[i].period);
    }
    return result;
}

double utilization_factor(Process processes[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (double)processes[i].burst_time / processes[i].period;
    }
    return sum;
}

double rms_threshold(int n) {
    return n * (pow(2.0, 1.0 / n) - 1);
}

void rate_monotonic_scheduling(Process processes[], int n) {
    int lcm_period = calculate_lcm(processes, n);
    printf("\nLCM of Periods = %d\n\n", lcm_period);

    printf("Rate Monotonic Scheduling:\n");
    printf("PID  Burst  Period\n");
    for (int i = 0; i < n; i++) {
        printf("%2d    %2d      %2d\n", processes[i].id, processes[i].burst_time, processes[i].period);
    }

    double utilization = utilization_factor(processes, n);
    double threshold = rms_threshold(n);
    printf("\nUtilization: %.6f <= %.6f => %s\n", utilization, threshold, (utilization <= threshold) ? "Schedulable" : "Not Schedulable");

    if (utilization > threshold) {
        printf("\nSystem may not be schedulable under Rate Monotonic Scheduling!\n");
        return;
    }

    int timeline = 0;
    while (timeline < lcm_period) {
        int selected = -1;
        int min_period = 1e9;

        for (int i = 0; i < n; i++) {
            if (timeline % processes[i].period == 0) {
                processes[i].remaining_time = processes[i].burst_time;
            }
            if (processes[i].remaining_time > 0 && processes[i].period < min_period) {
                min_period = processes[i].period;
                selected = i;
            }
        }

        if (selected != -1) {
            printf("Time %2d: Process %d is running\n", timeline, processes[selected].id);
            processes[selected].remaining_time--;
        } else {
            printf("Time %2d: CPU is idle\n", timeline);
        }
        timeline++;
    }
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_PROCESSES) {
        printf("Invalid number of processes. Must be between 1 and %d.\n", MAX_PROCESSES);
        return 1;
    }

    printf("Enter CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("Enter time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].period);
    }

    sort_by_period(processes, n);
    rate_monotonic_scheduling(processes, n);

    return 0;
}
