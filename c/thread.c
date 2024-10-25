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