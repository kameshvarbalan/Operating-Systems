#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTITIONS 10
#define MAX_PROCESSES 10

void firstFit(int partitions[], int partitionSize, int processes[], int processSize){
    int allocation[MAX_PROCESSES];
    for(int i=0; i<processSize; i++){
        allocation[i] = -1;
    }
    for(int i=0; i<processSize; i++){
        for(int j=0; j<partitionSize; j++){
            if(partitions[j]>=processes[i]){
                allocation[i] = j;
                partitions[j] = 0;
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\n");
    for(int i=0; i<processSize; i++){
        if(allocation[i]!=-1){
            printf("Process %d: Size %d -> Partition %d\n", i+1, processes[i], allocation[i]+1);
        } else{
            printf("Process %d: Size %d -> Not Allocated\n", i+1, processes[i]);
        }
    }
}

void bestFit(int partitions[], int partitionSize, int processes[], int processSize){
    int allocation[MAX_PROCESSES];
    for(int i=0; i<processSize; i++){
        allocation[i] = -1;
    }
    for(int i=0; i<processSize; i++){
        int bestIdx = -1;
        for(int j=0; j<partitionSize; j++){
            if(partitions[j]>=processes[i]){
                if(bestIdx==-1 || partitions[j]<partitions[bestIdx]){
                    bestIdx = j;
                }
            }
        }
        if(bestIdx!=-1){
            allocation[i] = bestIdx;
            partitions[bestIdx] = 0;
        }
    }
    printf("\nBest Fit Allocation:\n");
    for(int i=0; i<processSize; i++){
        if(allocation[i]!=-1){
            printf("Process %d: Size %d -> Partition %d\n", i+1, processes[i], allocation[i]+1);
        } else{
            printf("Process %d: Size %d -> Not Allocated\n", i+1, processes[i]);
        }
    }
}

void worstFit(int partitions[], int partitionSize, int processes[], int processSize){
    int allocation[MAX_PROCESSES];
    for(int i=0; i<processSize; i++){
        allocation[i] = -1;
    }
    for(int i=0; i<processSize; i++){
        int worstIdx = -1;
        for(int j=0; j<partitionSize; j++){
            if(partitions[j]>=processes[i]){
                if(worstIdx==-1 || partitions[j]>partitions[worstIdx]){
                    worstIdx = j;
                }
            }
        }
        if(worstIdx!=-1){
            allocation[i] = worstIdx;
            partitions[worstIdx] = 0;
        }
    }
    printf("\nWorst Fit Allocation:\n");
    for(int i=0; i<processSize; i++){
        if(allocation[i]!=-1){
            printf("Process %d: Size %d -> Partition %d\n", i+1, processes[i], allocation[i]+1);
        } else {
            printf("Process %d: Size %d -> Not Allocated\n", i+1, processes[i]);
        }
    }
}

int main(){
    printf("Name: Kameshvar Balan V\nRegNo: 22BCE3296\n\n");
    int partitions[MAX_PARTITIONS], processes[MAX_PROCESSES];
    int partitionSize, processSize;
    printf("Enter the number of partitions: ");
    scanf("%d", &partitionSize);
    printf("Enter the size of each partition:\n");
    for(int i=0; i<partitionSize; i++){
        printf("Partition %d size: ", i+1);
        scanf("%d", &partitions[i]);
    }
    printf("\nEnter the number of processes: ");
    scanf("%d", &processSize);
    printf("Enter the size of each process:\n");
    for(int i=0; i<processSize; i++){
        printf("Process %d size: ", i+1);
        scanf("%d", &processes[i]);
    }
    int FirstFit[MAX_PARTITIONS], BestFit[MAX_PARTITIONS], WorstFit[MAX_PARTITIONS];
    for (int i=0; i<partitionSize; i++){
        FirstFit[i] = partitions[i];
        BestFit[i] = partitions[i];
        WorstFit[i] = partitions[i];
    }
    firstFit(FirstFit, partitionSize, processes, processSize);
    bestFit(BestFit, partitionSize, processes, processSize);
    worstFit(WorstFit, partitionSize, processes, processSize);
    return 0;
}
