#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int counter = 0;
pthread_mutex_t mutex;

void* threadFunction(void* arg){
    printf("Thread %ld initializing\n", pthread_self());
    pthread_mutex_lock(&mutex);
    counter++;
    printf("Thread %ld incremented - Counter: %d\n", pthread_self(), counter);
    pthread_mutex_unlock(&mutex);
    int init_delay = rand()%7+1;
    sleep(init_delay);
    printf("Thread %ld finishing\n", pthread_self());
    pthread_mutex_lock(&mutex);
    counter--;
    printf("Thread %ld decremented - Counter: %d\n", pthread_self(), counter);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){
    printf("Name: Kameshvar Balan V\nRegNo: 22BCE3296\n\n");
    int numThreads;
    srand(time(NULL));
    printf("Enter the number of threads: ");
    scanf("%d", &numThreads);
    pthread_t threads[numThreads];
    if(pthread_mutex_init(&mutex, NULL)!=0){
        printf("Mutex initialization failed\n");
        return 1;
    }
    for(int i=0; i<numThreads; i++){
        if(pthread_create(&threads[i], NULL, threadFunction, NULL)!=0){
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }
    for(int i=0; i<numThreads; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("Final value of shared counter: %d\n", counter);
    return 0;
}
