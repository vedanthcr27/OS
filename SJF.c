#include<stdio.h>

typedef struct {
    int id,AT,BT,CT,TAT,WT,RT;
}Process;

void sortP(Process p[],int n)
{
    int i,j;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(p[j].AT>p[j+1].AT)
            {
            Process temp=p[j];
            p[j]=p[j+1];
            p[j+1]=temp;
            }
        }
    }
}

void sjfNP(Process p[], int n) {
    int completed = 0, time = 0, minIdx, totalTAT = 0, totalWT = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++)
        isCompleted[i] = 0;

    while (completed < n) {
        minIdx = -1;
        int minBurst = 100;
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && p[i].AT <= time && p[i].BT < minBurst) {
                minBurst = p[i].BT;
                minIdx = i;
            }
        }
        if (minIdx == -1)
        {
                time++;
                continue;
        }

        p[minIdx].CT = time + p[minIdx].BT;
        p[minIdx].TAT = p[minIdx].CT - p[minIdx].AT;
        p[minIdx].WT = p[minIdx].TAT - p[minIdx].BT;
        time = p[minIdx].CT;
        isCompleted[minIdx] = 1;
        totalTAT += p[minIdx].TAT;
        totalWT += p[minIdx].WT;
        completed++;
    }
    float avgTAT = (float)totalTAT / n;
    float avgWT = (float)totalWT / n;
    printf("TAT:%.2f AND WT:%.2f",avgTAT,avgWT);
}

int main()
{
    int n;
    printf("Enter n:");
    scanf("%d",&n);
    Process p[n];
    for(int i=0;i<n;i++)
    {
        p[i].id=i+1;
        printf("Enter AT:");
        scanf("%d",&p[i].AT);
        printf("Enter BT:");
        scanf("%d",&p[i].BT);
    }
    sjfNP(p,n);
    return 1;
}
