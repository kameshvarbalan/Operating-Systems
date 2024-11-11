#include <stdio.h>
#include <stdlib.h>

struct Process{
    int id, at, bt, ct, tat, wt, st, rt, priority;
};

int main(){
    printf("Name: Kameshvar Balan V\nRegNo: 22BCE3296\n\n");
    printf("Enter the number of processes: ");
    int n;
    scanf("%d", &n);
    struct Process arr[n];
    for(int i=0; i<n; i++){
        arr[i].id = i+1;
        printf("Enter burst time, arrival time and priority of process %d: ", i+1);
        scanf("%d %d %d", &arr[i].bt, &arr[i].at, &arr[i].priority);
        arr[i].rt = arr[i].bt;
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
    int time = 0;
    int total_wt = 0;
    int total_tat = 0;
    int completed = 0;
    printf("\nProcess\tPriority\tBurst_Time\tArrival_Time\tStart_Time\tCompletion_Time\tTurn_Around_Time\tWaiting_Time\n");
    while(completed<n){
        int min = -1;
        int highest_priority = INT32_MAX;
        for(int i=0; i<n; i++){
            if(arr[i].at<=time && arr[i].rt>0 && arr[i].priority<highest_priority){
                highest_priority = arr[i].priority;
                min = i;
            } }
        if(min != -1){
            if(arr[min].bt == arr[min].rt){
                arr[min].st = time;
            }
            arr[min].rt -= 1;
            if(arr[min].rt == 0){
                arr[min].ct = time + 1;
                arr[min].tat = arr[min].ct - arr[min].at;
                arr[min].wt = arr[min].tat - arr[min].bt;
                total_wt += arr[min].wt;
                total_tat += arr[min].tat;
                completed++;
                printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", arr[min].id, arr[min].priority, arr[min].bt, arr[min].at, arr[min].st, arr[min].ct, arr[min].tat, arr[min].wt);
            } }
        time++;
    }
    double avg_wt = 1.0*total_wt / n;
    double avg_tat = 1.0*total_tat / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turn Around Time: %.2f\n", avg_tat);
    return 0; }