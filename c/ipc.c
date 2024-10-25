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
