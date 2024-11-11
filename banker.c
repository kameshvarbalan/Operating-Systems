#include <stdio.h>
#include <stdbool.h>

void deadlock(int processes[], int avail[], int max[][10], int alloc[][10], int n, int m){
    int need[10][10];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    bool finish[10] = {0};
    int safeSeq[10];
    int work[10];
    for(int i=0; i<m; i++){
        work[i] = avail[i];
    }
    int count = 0;
    while(count<n){
        bool found = false;
        for(int p=0; p<n; p++){
            if(finish[p]==false){
                int j;
                for(j=0; j<m; j++){
                    if(need[p][j] > work[j]){
                        break;
                    }
                }
                if(j==m){
                    for(int k=0; k<m; k++){
                        work[k] += alloc[p][k];
                    }
                    safeSeq[count++] = processes[p];
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if(!found){
            printf("\nSystem is not in a safe state.\n");
            printf("Deadlock detected - Processes involved: ");
            for(int p=0; p<n; p++){
                if(finish[p]==false){
                    printf("P%d ", processes[p]+1);
                }
            }
            printf("\n");
            return;
        }
    }
    printf("\nSystem is in a safe state\nSafe sequence : ");
    for(int i=0; i<n; i++){
        printf("P%d ", safeSeq[i] + 1);
    }
    printf("\n");
}

int main(){
    printf("Name: Kameshvar Balan V\nRegNo: 22BCE3296\n\n");
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource: ");
    scanf("%d", &m);
    int processes[10];
    for(int i=0; i<n; i++){
        processes[i] = i;
    }
    int avail[10];
    printf("Enter the available instances for each resource: ");
    for(int i=0; i<m; i++){
        scanf("%d", &avail[i]);
    }
    int max[10][10];
    printf("Enter the maximum resources required by each process\n");
    for(int i=0; i<n; i++){
        printf("Process P%d: ", i+1);
        for(int j=0; j<m; j++){
            scanf("%d", &max[i][j]);
        }
    }
    int alloc[10][10];
    printf("Enter the allocated resources for each process\n");
    for(int i=0; i<n; i++){
        printf("Process P%d: ", i+1);
        for(int j=0; j<m; j++){
            scanf("%d", &alloc[i][j]);
        }
    }
    deadlock(processes, avail, max, alloc, n, m);
    return 0;
}
