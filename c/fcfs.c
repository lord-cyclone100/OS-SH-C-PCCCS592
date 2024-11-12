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