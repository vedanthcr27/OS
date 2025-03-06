#include <stdio.h>

struct Process {
    int id;
    int bt;
    int at;
};

void sortProcessesByArrival(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].at > proc[j].at) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

int main() {
    float avgtat,avgwt;
    int n,sumw=0,sumt=0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        printf("Enter burst time and arrival time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].bt, &proc[i].at);
        proc[i].id = i + 1;
    }


    sortProcessesByArrival(proc, n);

    int wt[n], tat[n];


    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + proc[i - 1].bt;
    }


    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].bt + wt[i];
    }

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i=0; i<n;i++){
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].bt, proc[i].at,wt[i],tat[i]);
    }
    printf("\nAverage TAT :");
    for(int i=0;i<n;i++){
        sumt=sumt+tat[i];
        avgtat=sumt/n;
        printf("%f",avgtat);
    }
    printf("\nAverage WT :");
    for(int i=0;i<n;i++){
        sumw=sumw+wt[i];
        avgwt=sumw/n;
        printf("%f",avgwt);

    }

}
