#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

sem_t mutex, writeBlock;
int data = 0;
int readCount = 0; 

void* reader(void* arg) {
    int reader_id = *((int*)arg);
    sem_wait(&mutex);
    readCount++;
    if(readCount==1){
        sem_wait(&writeBlock);
    }
    sem_post(&mutex);
    printf("Reader %d: Read data %d\n", reader_id, data);
    sleep(rand()%2+1);
    sem_wait(&mutex);
    readCount--;
    if(readCount==0){
        sem_post(&writeBlock);
    }
    sem_post(&mutex);
    return NULL;
}

void* writer(void* arg) {
    int writer_id = *((int*)arg);
    sem_wait(&writeBlock);
    data++;
    printf("Writer %d: Wrote data %d\n", writer_id, data);
    sleep(rand()%2+1);
    sem_post(&writeBlock);
    return NULL;
}

int main(){
    pthread_t r_threads[5], w_threads[5];
    int r_ids[5], w_ids[5];
    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);
    int num_readers, num_writers;
    printf("Enter the number of readers: ");
    scanf("%d", &num_readers);
    printf("Enter the number of writers: ");
    scanf("%d", &num_writers);
    for(int i=0; i<num_readers; i++){
        r_ids[i] = i + 1;
        pthread_create(&r_threads[i], NULL, reader, &r_ids[i]);
    }
    for(int i=0; i<num_writers; i++){
        w_ids[i] = i + 1;
        pthread_create(&w_threads[i], NULL, writer, &w_ids[i]);
    }
    for(int i=0; i<num_readers; i++){
        pthread_join(r_threads[i], NULL);
    }
    for(int i=0; i<num_writers; i++){
        pthread_join(w_threads[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&writeBlock);
    return 0;
}
