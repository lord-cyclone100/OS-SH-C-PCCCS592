#### Write a C program to create a child process and print the id's of the parent process and child process

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){

    pid_t pid;
    pid = fork();
    
    printf("Current process : %d\tParent process : %d\n",getpid(),getppid());

    if(pid == 0){
        printf("Current process : %d\tParent process : %d\n",getpid(),getppid());
    }
    else{
        //wait(NULL);
        printf("Current process : %d\tParent process : %d\n",getpid(),getppid());
    }

    return 0;
}
```

#### Write a C program to demonstrate interprocess communication between a parent process and it's child process using pipe()

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int main(){
    int fd[2];
    char str[] = "hello\n";
    pid_t pid;
    char readbuffer[80];

    int p = pipe(fd);

    if(p < 0){
        printf("Pipe not created");
        exit(0);
    }

    pid = fork();
    if(pid < 0){
        printf("Fork creation error");
    }

    else if(pid == 0){  //child process
        close(fd[0]);
        printf("Child process writing string %s into buffer\n",str);
        write(fd[1],str, strlen(str)+1);
        close(fd[1]);
        exit(0);
    }

    else{   //parent process
        close(fd[1]);
        printf("Parent process reading string %s from buffer\n",str);
        read(fd[0],readbuffer,sizeof(readbuffer));
        printf("String read : %s",readbuffer);
        close(fd[0]);
    }

    return 0;
}
```

#### Write a C program to add to matrices using threads

```c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;
int r1,c1,r2,c2,A[10][10],B[10][10];

void* matrixInput(){
    pthread_mutex_lock(&myMutex);
    printf("Enter the rows and columns of matrix A : ");
    scanf("%d %d",&r1,&c1);
    printf("Enter matrix A elements :\n");
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            scanf("%d",&A[i][j]);
        }
    }
    printf("Enter the rows and columns of matrix B : ");
    scanf("%d %d",&r2,&c2);
    printf("Enter matrix B elements :\n");
    for(int i=0;i<r2;i++){
        for(int j=0;j<c2;j++){
            scanf("%d",&B[i][j]);
        }
    }
    pthread_mutex_unlock(&myMutex);
}

void* matrixSum(){
    int C[10][10];
    pthread_mutex_lock(&myMutex);
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            C[i][j] = A[i][j]+B[i][j];
        }
    }
    printf("Matrix sum :\n");
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            printf("%d ",C[i][j]);
        }
        printf("\n");
    }
    pthread_mutex_unlock(&myMutex);    
}

int main(){
    pthread_t thread1, thread2;
    pthread_create(&thread1,NULL,&matrixInput,NULL);
    pthread_create(&thread2,NULL,&matrixSum,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    return 0;
}
```

#### Write a C program to demonstrate producer-consumer problem using semaphores

```c
#include <stdio.h>
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
}
```

#### Write a C program to demonstrate Dining Philosophers problem using semaphores

```c
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
```

#### The process ids, arrival time and burst time for a set of processes are given. Write a C program to display the details of the processes along with thw waiting time and turnaround time for each process using First Come First Serve CPU scheduling algorithm. Also find the average waiting time and average turnaround time.

<table>
  <tr>
    <th>Process</th>
    <th>Arrival Time</th>
    <th>Burst Time</th>
  </tr>
  <tr>
    <td>P0</td>
    <td>0</td>
    <td>4</td>
  </tr>
  <tr>
    <td>P1</td>
    <td>1</td>
    <td>3</td>
  </tr>
  <tr>
    <td>P2</td>
    <td>2</td>
    <td>1</td>
  </tr>
  <tr>
    <td>P3</td>
    <td>3</td>
    <td>5</td>
  </tr>
  <tr>
    <td>P4</td>
    <td>4</td>
    <td>2</td>
  </tr>
</table>




```c
#include <stdio.h>

struct Process{
    int id;
    int arrivalTime;
    int burstTime;
};

int i,j;

void printProcess(struct Process p) {
    printf("Process ID: %d\n", p.id);
    printf("Arrival Time: %d\n", p.arrivalTime);
    printf("Burst Time: %d\n", p.burstTime);
    printf("\n");
}

void fcfsScheduling(struct Process *p,int n){
    for(i=0;i<n-1;i++){
        int flag = 0;
        for(j=0;j<n-i-1;j++){
            if(p[j].arrivalTime>p[j+1].arrivalTime){
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
                flag = 1;
            }
        }
        if(flag==0){
            break;
        }
    }
    int  currentTime = 0;
    double sumWaitTime = 0;
    for(i=0;i<n;i++){
        int wt = currentTime-p[i].arrivalTime;
        printf("Waiting time of process P%d : %d\n",i,wt);
        sumWaitTime += wt;
        currentTime += p[i].burstTime;
    }
    printf("Average waiting time : %f\n",(sumWaitTime/n));

    printf("\n");

    currentTime = 0;
    double turnAroundTime = 0;
    for(i=0;i<n;i++){
        currentTime += p[i].burstTime;
        int tat = currentTime-p[i].arrivalTime;
        printf("Turnaround time of process P%d : %d\n",i,tat);
        turnAroundTime += tat;
    }
    printf("Average turnaround time : %f",(turnAroundTime/n));
}

int main(){

    struct Process process[] = {
        {0,0,4},
        {1,1,3},
        {2,2,1},
        {3,3,5},
        {4,4,2}
    };

    int n = sizeof(process)/sizeof(process[0]);

    for(int i=0;i<n;i++){
        printProcess(process[i]);
    }

    fcfsScheduling(process, n);

    return 0;
}
```
