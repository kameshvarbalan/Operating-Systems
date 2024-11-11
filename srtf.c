#include <stdio.h>
#include <stdlib.h>

struct Process{
    int id, at, bt, ct, tat, wt, st, rt;
};

int main(){
    printf("Name: Kameshvar Balan V\nRegNo: 22BCE3296\n\n");
    printf("Enter number of processes: ");
    int n;
    scanf("%d", &n);
    struct Process arr[n];
    for(int i=0; i<n; i++){
        arr[i].id = i+1;
        printf("Enter burst time and arrival time of process id %d: ", i+1);
        scanf("%d %d", &arr[i].bt, &arr[i].at);
        arr[i].rt = arr[i].bt;
    }
    int completed = 0, time = 0;
    int min = -1;
    while(completed<n){
        min = -1;
        int burst = INT32_MAX;
        for(int i=0; i<n; i++){
            if(arr[i].at<=time && arr[i].rt>0 && arr[i].rt<burst){
                min = i;
                burst = arr[i].rt;
            }
        }
        if(min!=-1){
            if(arr[min].bt==arr[min].rt){
                arr[min].st = time;
            }
            arr[min].rt -= 1;
            if(arr[min].rt==0){
                arr[min].ct = time+1;
                arr[min].tat = arr[min].ct - arr[min].at;
                arr[min].wt = arr[min].tat - arr[min].bt;
                completed++;
            }
        }
        time++;
    }
    int wt = 0;
    int tat = 0;
    printf("\nProcess\tBurst_Time\tArrival_Time\tStart_Time\tCompletion_Time\tTurn_Around_Time\tWaiting_Time\n");
    for(int i=0; i<n; i++){
        wt += arr[i].wt;
        tat += arr[i].tat;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", arr[i].id, arr[i].bt, arr[i].at, arr[i].st, arr[i].ct, arr[i].tat, arr[i].wt);
    }
    double avgWt = 1.0*wt/n;
    double avgTat = 1.0*tat/n;
    printf("\nAverage Waiting Time: %.2f\n", avgWt);
    printf("Average Turn Around Time: %.2f\n", avgTat);
    return 0;
}