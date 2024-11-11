#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

int *buffer;
int buffer_size;
int in = 0;
int out = 0;
int items;
int items_produced = 0;
int items_consumed = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void* producer(void* arg){
    while(1){
        int item = rand()%10;
        if(items_produced>=items){
            break;
        }
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        if(items_produced<items){
            buffer[in] = item;
            printf("Producer produced: %d at index %d\n", item, in);
            in = (in+1)%buffer_size;
            items_produced++;
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(rand()%2+1);
    }
    return NULL;
}

void* consumer(void* arg){
    int item;
    while(1){
        if (items_consumed>=items){
            break;
        }
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        if(items_consumed<items){
            item = buffer[out];
            printf("Consumer consumed: %d from index %d\n", item, out);
            out = (out+1)%buffer_size;
            items_consumed++;
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(rand()%2+1);
    }
    return NULL;
}

int main(){
    pthread_t prod_thread, cons_thread;
    printf("Enter the buffer size: ");
    scanf("%d", &buffer_size);
    buffer = (int*)malloc(buffer_size*sizeof(int));
    printf("Enter total number of items: ");
    scanf("%d", &items);
    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    free(buffer);
    printf("All items produced and consumed successfully\n");
    return 0;
}
