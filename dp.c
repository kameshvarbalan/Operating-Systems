#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t forks[5];
sem_t order_sem;
int meals_eaten[5];
int num_philosophers;

void think(int philosopher_id){
    printf("Philosopher %d is thinking\n", philosopher_id);
    sleep(rand()%2+1);
}

void eat(int philosopher_id){
    printf("Philosopher %d is eating\n", philosopher_id);
    printf("Philosopher %d has finished eating\n", philosopher_id);
    printf("Philosopher %d put down forks\n", philosopher_id);
}

void* philosopher(void* num) {
    int philosopher_id = *(int*)num;
    if(philosopher_id==0){
        sem_wait(&order_sem);
    } 
    else if(philosopher_id==2 || philosopher_id==4){
        sem_wait(&order_sem);
    }
    while(meals_eaten[philosopher_id]!=1){
        think(philosopher_id);
        printf("Philosopher %d is hungry\n", philosopher_id);
        sem_wait(&forks[philosopher_id]);
        printf("Philosopher %d picked up fork %d\n", philosopher_id, philosopher_id);
        sem_wait(&forks[(philosopher_id + 1) % num_philosophers]);
        printf("Philosopher %d picked up fork %d\n", philosopher_id, (philosopher_id + 1) % num_philosophers);
        eat(philosopher_id);
        meals_eaten[philosopher_id]++;
        sem_post(&forks[philosopher_id]);
        sem_post(&forks[(philosopher_id + 1) % num_philosophers]);
    }
    if(philosopher_id==1 || philosopher_id==3){
        sem_post(&order_sem);
    } 
    else if(philosopher_id==0){
        sem_post(&order_sem);
    }
    return NULL;
}

int main(){
    printf("Enter the number of philosophers: ");
    scanf("%d", &num_philosophers);
    for(int i=0; i<num_philosophers; i++){
        sem_init(&forks[i], 0, 1);
        meals_eaten[i] = 0;
    }
    sem_init(&order_sem, 0, 0);
    pthread_t philosophers[num_philosophers];
    int philosopher_ids[num_philosophers];
    for (int i=0; i<num_philosophers; i++){
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }
    sem_post(&order_sem);
    sem_post(&order_sem);
    for (int i=0; i<num_philosophers; i++){
        pthread_join(philosophers[i], NULL);
    }
    for(int i=0; i<num_philosophers; i++){
        sem_destroy(&forks[i]);
    }
    sem_destroy(&order_sem);
    printf("All philosophers have finished eating\n");
    return 0;
}
