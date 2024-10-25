/*#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t empty, mutex1, full;
int buffer[6], in = 0, out = 0, item1 = 0, item2;

void *producer(void* a){
    while(1){
        sem_wait(&empty);
        sem_wait(&mutex1);
        item1++;
        buffer[in] = item1;
        printf("Producer %d produce item %d\n",*(int*)a,item1);
        in = (in+1)%6;
        sem_post(&mutex1);
        sem_post(&full);
        sleep(1);
    }
}

void *consumer(void* a){
    while(1){
        sem_wait(&full);
        sem_wait(&mutex1);
        item2 = buffer[out];
        printf("Consumer %d consume item %d\n",*(int*)a,item1);
        out = (out+1)%6;
        sem_post(&mutex1);
        sem_post(&empty);
    }
}

int main(){
    int i, c, p;
    printf("Enter the number of producers:");
    scanf("%d",&p);
    printf("Enter the number of consumers:");
    scanf("%d",&c);
    sem_init(&empty,0,6);
    sem_init(&full,0,0);
    sem_init(&mutex1,0,1);
    pthread_t th1[10], th2[10];
    for(i=0;i<p;i++){
        pthread_create(&th1[i],NULL,producer,(int*)&i);
    }
    for(i=0;i<c;i++){
        pthread_create(&th2[i],NULL,consumer,(int*)&i);
    }
    for(i=0;i<p;i++){
        pthread_join(th1[i],NULL);
    }
    for(i=0;i<c;i++){
        pthread_join(th2[i],NULL);
    }

    return 0;
}*/


#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t empty, mutex, full;
int buffer[10], in = 0, out = 0, item1 = 0, item2;

void *producer(void *a)  {
  while (1) {
    sem_wait(&empty);
    sem_wait(&mutex);

    item1++;
    buffer[in] = item1;
    printf("Producer %d produces item %d \n", *(int *)a, item1);
    in = (in + 1) % 10;

    sem_post(&mutex);
    sem_post(&full);

    sleep(1);
  }
}

void *consumer(void *a) {
  while (1) {
    sem_wait(&full);
    sem_wait(&mutex);

    item2 = buffer[out];
    printf("Consumer %d consumes item %d \n", *(int *)a, item2);
    out = (out + 1) % 10;

    sem_post(&mutex);
    sem_post(&empty);
  }
}

int main() {
  int i, c, p;

  printf("Enter no of producers p: ");
  scanf("%d", &p);

  printf("Enter no of consumers c: ");
  scanf("%d", &c);

  sem_init(&empty, 0, 10);
  sem_init(&full,0 , 0);
  sem_init(&mutex, 0, 1);
  
  pthread_t thread1[10], thread2[10];

  for (int i = 0; i < p; i++) {
    pthread_create(&thread1[i], NULL, producer, (int *)&i);
  }

  for (int i = 0; i < c; i++) {
    pthread_create(&thread2[i], NULL, consumer, (int *)&i);
  }

  for (int i = 0; i < p; i++) {
    pthread_join(thread1[i], NULL);
  }

  for (int i = 0; i < c; i++) {
    pthread_join(thread2[i], NULL);
  }

  return 0;
}