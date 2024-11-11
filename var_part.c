#include <stdio.h>
#include <stdlib.h>

void firstFit(int blockSize[], int m, int processSize[], int n){
    int allocation[n];
    for(int i=0; i<n; i++) 
        allocation[i] = -1;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(blockSize[j]>=processSize[i]){
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\n");
    printf("Process\tSize\tBlock\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t", i+1, processSize[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n){
    int allocation[n];
    for(int i=0; i<n; i++)
        allocation[i] = -1;
    for(int i=0; i<n; i++){
        int bestIdx = -1;
        for(int j=0; j<m; j++){
            if(blockSize[j]>=processSize[i]){
                if(bestIdx==-1 || blockSize[j]<blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if(bestIdx!=-1){
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    printf("\nBest Fit Allocation:\n");
    printf("Process\tSize\tBlock\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t", i+1, processSize[i]);
        if(allocation[i]!=-1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n){
    int allocation[n];
    for(int i=0; i<n; i++)
        allocation[i] = -1;
    for(int i=0; i<n; i++){
        int worstIdx = -1;
        for(int j=0; j<m; j++){
            if(blockSize[j]>=processSize[i]){
                if(worstIdx==-1 || blockSize[j]>blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if(worstIdx!=-1){
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    printf("\nWorst Fit Allocation:\n");
    printf("Process\tSize\tBlock\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t", i+1, processSize[i]);
        if (allocation[i]!=-1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }
}

int main(){
    printf("Name: Kameshvar Balan V\nRegNo: 22BCE3296\n\n");
    int m, n;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    int blockSize[m];
    printf("Enter the sizes of the memory blocks:\n");
    for(int i=0; i<m; i++){
        printf("Block %d size: ", i+1);
        scanf("%d", &blockSize[i]);
    }
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    int processSize[n];
    printf("Enter the sizes of the processes:\n");
    for(int i=0; i<n; i++){
        printf("Process %d size: ", i+1);
        scanf("%d", &processSize[i]);
    }
    int blockSize1[m], blockSize2[m], blockSize3[m];
    for(int i=0; i<m; i++){
        blockSize1[i] = blockSize[i];
        blockSize2[i] = blockSize[i];
        blockSize3[i] = blockSize[i];
    }
    firstFit(blockSize1, m, processSize, n);
    bestFit(blockSize2, m, processSize, n);
    worstFit(blockSize3, m, processSize, n);
    return 0;
}
