#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t chopstick[5];
int p;

void* diningPhilosopher(void* a){
    while(1){
        int i=*(int*)a;
        sem_wait(&chopstick[i]);
        sem_wait(&chopstick[(i+1)%p]);
        printf("Philosopher %d is holding chopsticks %d and %d\n",i,i,(i+1)%5);
        printf("Philosopher %d is now eating\n",i);
        sleep(1);
        sem_post(&chopstick[i]);
        sem_post(&chopstick[(i+1)%p]);
        printf("Philosopher %d is now thinking\n",*(int*)a);
    }
}

int main(){

    int j;
    printf("Enter the number of philosophers : ");
    scanf("%d",&p);
    for(j=0;j<p;j++){
        sem_init(&chopstick[j],0,1);
    }
    pthread_t th[10];
    for(j=0;j<p;j++){
        pthread_create(&th[j],NULL,&diningPhilosopher,(int*)&j);
    }
    for(j=0;j<p;j++){
        pthread_join(th[j],NULL);
    }

    return 0;
}