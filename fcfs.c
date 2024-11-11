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
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j].at>arr[j+1].at){
                struct Process temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    int wt = 0;
    int tat = 0;
    int time = 0;
    printf("\nProcess\tBurst_Time\tArrival_Time\tStart_Time\tCompletion_Time\tTurn_Around_Time\tWaiting_Time\n");
    for(int i=0; i<n; i++){
        if(time < arr[i].at){
            time = arr[i].at;
        }
        arr[i].st = time;
        arr[i].ct = arr[i].st + arr[i].bt;
        arr[i].tat = arr[i].ct - arr[i].at;
        arr[i].wt = arr[i].tat - arr[i].bt;
        time = arr[i].ct;
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