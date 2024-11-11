#include <stdio.h>
#include <stdlib.h>

struct Process{
    int id, at, bt, ct, tat, wt, st, priority;
};

int main(){
    printf("Enter the number of processes: ");
    int n;
    scanf("%d", &n);
    struct Process arr[n];
    for(int i=0; i<n; i++){
        arr[i].id = i+1;
        printf("Enter burst time, arrival time and priority of process %d: ", i+1);
        scanf("%d %d %d", &arr[i].bt, &arr[i].at, &arr[i].priority);
    }
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j].priority > arr[j+1].priority || 
               (arr[j].priority == arr[j+1].priority && arr[j].at>arr[j+1].at)){
                struct Process temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    int currentTime = 0;
    int total_wt = 0;
    int total_tat = 0;
    printf("\nProcess\tPriority\tBurst_Time\tArrival_Time\tStart_Time\tCompletion_Time\tTurn_Around_Time\tWaiting_Time\n");
    for (int i = 0; i < n; i++) {
        if (currentTime < arr[i].at) {
            currentTime = arr[i].at;
        }
        arr[i].st = currentTime;
        arr[i].ct = arr[i].st + arr[i].bt;
        arr[i].tat = arr[i].ct - arr[i].at;
        arr[i].wt = arr[i].tat - arr[i].bt;
        currentTime = arr[i].ct;
        total_wt += arr[i].wt;
        total_tat += arr[i].tat;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", arr[i].id, arr[i].priority, arr[i].bt, arr[i].at, arr[i].st, arr[i].ct, arr[i].tat, arr[i].wt);
    }
    double avg_wt = 1.0*total_wt / n;
    double avg_tat = 1.0*total_tat / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turn Around Time: %.2f\n", avg_tat);
    return 0; 
}