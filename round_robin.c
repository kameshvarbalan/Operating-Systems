#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Process{
    int id, at, bt, ct, tat, wt, st, rt;
    bool q;
};

struct Queue{
    int front, rear, size;
    int capacity;
    int* arr;
};
struct Queue* createQueue(){
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = 25;
    queue->front = queue->size = 0;
    queue->rear = 25-1;
    queue->arr = (int*) malloc(queue->capacity * sizeof(int));
    return queue;
}
bool isFull(struct Queue* queue){
    return (queue->size==queue->capacity);
}
bool isEmpty(struct Queue* queue){
    return (queue->size==0);
}
void enqueue(struct Queue* queue, int item){
    if(isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = item;
    queue->size = queue->size + 1;
}
int dequeue(struct Queue* queue){
    if(isEmpty(queue))
        return -1;
    int item = queue->arr[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

int main(){
    printf("Enter number of processes: ");
    int n;
    scanf("%d", &n);
    struct Process processes[n];
    for(int i=0; i<n; i++){
        processes[i].id = i + 1;
        printf("Enter burst time and arrival time of process id %d: ", i + 1);
        scanf("%d %d", &processes[i].bt, &processes[i].at);
        processes[i].rt = processes[i].bt;
        processes[i].q = false;
    }
    int quantum;
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);
    struct Queue* queue = createQueue();
    int time = 0, completed = 0;  
    for(int i=0; i<n; i++){
        if(processes[i].at<=time){
            enqueue(queue, i);
            processes[i].q = true;
        }
    }
    while(completed<n){
        int current = dequeue(queue);
        if(current==-1){
            time++;
            for(int i=0; i<n; i++){
                if(processes[i].at<=time && processes[i].rt>0 && !processes[i].q){
                    enqueue(queue, i);
                    processes[i].q = true;
                }
            }
            continue;
        }
        if(processes[current].bt==processes[current].rt){
            processes[current].st = time;
        }
        if(processes[current].rt<=quantum){
            processes[current].ct = time+processes[current].rt;
            processes[current].rt = 0;
            processes[current].tat = processes[current].ct - processes[current].at;
            processes[current].wt = processes[current].tat - processes[current].bt;
            processes[current].q = false;
            for(int k=time+1; k<=processes[current].ct; k++){
                for(int i=0; i<n; i++){
                    if(processes[i].at<=k && processes[i].rt>0 && !processes[i].q){
                        enqueue(queue, i);
                        processes[i].q = true;
                    }
                }
            }
            time = processes[current].ct;
            completed++;
        }
        else{
            processes[current].rt -= quantum;
            for(int k=time+1; k<=time+quantum; k++){
                for(int i=0; i<n; i++){
                    if(processes[i].at<=k && processes[i].rt>0 && !processes[i].q){
                        enqueue(queue, i);
                        processes[i].q = true;
                    }
                }
            }
            time += quantum;
            enqueue(queue, current);
        }
    }
    int wt = 0, tat = 0; 
    printf("\nProcess\tBurst_Time\tArrival_Time\tStart_Time\tCompletion_Time\tTurn_Around_Time\tWaiting_Time\n");
    for(int i=0; i<n; i++){
        wt += processes[i].wt;
        tat += processes[i].tat;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].id, processes[i].bt, processes[i].at, processes[i].st, processes[i].ct, processes[i].tat, processes[i].wt);
    }
    double avg_wt = 1.0*wt / n;
    double avg_tat = 1.0*tat / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turn Around Time: %.2f\n", avg_tat);
    return 0;
}