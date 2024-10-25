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