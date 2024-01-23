#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"


int main(){
    int parent_pipe[2];
    int child_pipe[2];

    pipe(parent_pipe);
    pipe(child_pipe);

    char buff[10];
    int pid;
    pid = fork();

    if (pid < 0) {
        printf("FATAL: fork errors\n");
        exit(1);
    }
    else if (pid == 0){
        close(parent_pipe[1]);
        close(child_pipe[0]);

        read(parent_pipe[0], buff, 6);

        printf("%d: recieved %s \n", getpid(), buff);
        // read(parent_pipe[0], buff, 8);
        // printf("%d: recieved %s \n", getpid(), buff);

        write(child_pipe[1], "pong", 10);


        close(child_pipe[1]);
        close(parent_pipe[0]);
    }

    else{
        close(child_pipe[1]);
        close(parent_pipe[0]);
        write(parent_pipe[1], "ping", 4);
        write(parent_pipe[1], "DingDIng", 8);


        read(child_pipe[0], buff, 4);
        printf("%d: recieved %s \n", getpid(), buff);


        close(child_pipe[0]);
        close(parent_pipe[1]);

    }
    exit(0);
}