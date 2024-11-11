#include <stdio.h>
#include <stdlib.h>

void FCFS(int requests[], int n, int head){
    int total_seek_time = 0;
    printf("\nFCFS Order: %d -> ", head);
    for(int i=0; i<n; i++){
        total_seek_time += abs(head-requests[i]);
        head = requests[i];
        printf("%d -> ", head);
    }
    printf("End\nTotal Seek Time: %d\n", total_seek_time);
}

void SSTF(int requests[], int n, int head){
    int visited[n], total_seek_time = 0;
    for(int i=0; i<n; i++)
        visited[i] = 0;
    
    printf("\nSSTF Order: %d -> ", head);
    for(int i=0; i<n; i++){
        int min_distance = __INT_MAX__, index = -1;
        for(int j=0; j<n; j++){
            if(!visited[j] && abs(head-requests[j])<min_distance){
                min_distance = abs(head-requests[j]);
                index = j;
            }
        }
        visited[index] = 1;
        total_seek_time += min_distance;
        head = requests[index];
        printf("%d -> ", head);
    }
    printf("End\nTotal Seek Time: %d\n", total_seek_time);
}

void SCAN(int requests[], int n, int head, int disk_size, int direction){
    int total_seek_time = 0;
    int sorted[n+1];
    for(int i=0; i<n; i++)
        sorted[i]=requests[i];
    sorted[n] = (direction == 1)? disk_size-1:0;
    n++;
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(sorted[j]>sorted[j+1]){
                int temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    int idx;
    for(int i=0; i<n; i++){
        if(sorted[i]>head){
            idx = i;
            break;
        }
    }
    printf("\nSCAN Order: %d -> ", head);
    if(direction==1){
        for(int i=idx; i<n; i++){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
        for(int i=idx-1; i>-1; i--){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
    }
    else{
        for (int i=idx-1; i>-1; i--){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
        for(int i=idx; i<n; i++){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
    }
    printf("End\nTotal Seek Time: %d\n", total_seek_time);
}

void CSCAN(int requests[], int n, int head, int disk_size, int direction){
    int total_seek_time = 0;
    int sorted[n+2];
    for(int i=0; i<n; i++) 
        sorted[i] = requests[i];
    sorted[n] = disk_size-1;
    sorted[n+1] = 0;
    n += 2;
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(sorted[j]>sorted[j+1]){
                int temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    int idx;
    for(int i=0; i<n; i++){
        if(sorted[i]>head){
            idx = i;
            break;
        }
    }
    printf("\nC-SCAN Order: %d -> ", head);
    if(direction==1){
        for(int i=idx; i<n; i++){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
        for(int i=0; i<idx; i++){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
    } 
    else{
        for(int i=idx-1; i>=0; i--){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
        for(int i=n-1; i>=idx; i--){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
    }
    printf("End\nTotal Seek Time: %d\n", total_seek_time);
}

void LOOK(int requests[], int n, int head, int direction){
    int total_seek_time = 0;
    int sorted[n];
    for(int i=0; i<n; i++) 
        sorted[i] = requests[i];
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(sorted[j]>sorted[j+1]){
                int temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    int idx;
    for(int i=0; i<n; i++){
        if(sorted[i]>head){
            idx = i;
            break;
        }
    }
    printf("\nLOOK Order: %d -> ", head);
    if(direction==1){
        for(int i=idx; i<n; i++){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
        for(int i=idx-1; i>=0; i--){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
    }
    else{
        for(int i=idx-1; i>=0; i--){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
        for(int i=idx; i<n; i++){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
    }
    printf("End\nTotal Seek Time: %d\n", total_seek_time);
}

void CLOOK(int requests[], int n, int head, int direction){
    int total_seek_time = 0;
    int sorted[n];
    for(int i=0; i<n; i++)
        sorted[i] = requests[i];
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if (sorted[j] > sorted[j+1]){
                int temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    int idx;
    for(int i=0; i<n; i++){
        if(sorted[i]>head){
            idx = i;
            break;
        }
    }
    printf("\nC-LOOK Order: %d -> ", head);
    if(direction==1){
        for(int i=idx; i<n; i++){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
        for(int i=0; i<idx; i++){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
    } 
    else{
        for(int i=idx-1; i>=0; i--){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
        for(int i=n-1; i>=idx; i--){
            total_seek_time += abs(head-sorted[i]);
            head = sorted[i];
            printf("%d -> ", head);
        }
    }
    printf("End\nTotal Seek Time: %d\n", total_seek_time);
}

int main(){
    int n, head, disk_size, direction;
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the total disk size: ");
    scanf("%d", &disk_size);
    printf("Enter the direction (1 for right, 0 for left): ");
    scanf("%d", &direction);
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the requests: ");
    for(int i=0; i<n; i++){
        scanf("%d", &requests[i]);
    }
    FCFS(requests, n, head);
    SSTF(requests, n, head);
    SCAN(requests, n, head, disk_size, direction);
    CSCAN(requests, n, head, disk_size, direction);
    LOOK(requests, n, head, direction);
    CLOOK(requests, n, head, direction);
    return 0;
}
