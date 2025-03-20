#include <stdio.h>
#include <limits.h>

typedef struct {
    int id;
    int at;
    int bt;
    int pr;
    int remaining_time;
    int ct;
    int tat;
    int wt;
    int completed;
} Process;

void inputProcesses(Process p[], int n);
void sortByArrival(Process p[], int n);
void computePriorityScheduling(Process p[], int n);
void displayProcesses(Process p[], int n);

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    inputProcesses(p, n);
    sortByArrival(p, n);
    computePriorityScheduling(p, n);
    displayProcesses(p, n);

    float totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }
    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f", totalWT / n);

    return 0;
}

void inputProcesses(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].remaining_time = p[i].bt;
        p[i].completed = 0;
    }
}

void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void computePriorityScheduling(Process p[], int n) {
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int highestPriorityIndex = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= currentTime && p[i].remaining_time > 0) {
                if (p[i].pr < highestPriority) {
                    highestPriority = p[i].pr;
                    highestPriorityIndex = i;
                }
            }
        }

        if (highestPriorityIndex == -1) {
            currentTime++;
            continue;
        }

        Process *proc = &p[highestPriorityIndex];
        proc->remaining_time--;
        currentTime++;

        if (proc->remaining_time == 0) {
            proc->ct = currentTime;
            proc->tat = proc->ct - proc->at;
            proc->wt = proc->tat - proc->bt;
            proc->completed = 1;
            completed++;
        }
    }
}

void displayProcesses(Process p[], int n) {
    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].pr, p[i].ct, p[i].tat, p[i].wt);
    }
}
