#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void primes(int left_pipe[2]){
    int right_pipe[2];
    pipe(right_pipe);

    int num;
    read(left_pipe[0], &num, sizeof(int));
    if (num == 0){
        exit(0);
    }
    printf("prime %d \n", num);

    if(fork() == 0){
        close(left_pipe[0]);
        // close(left_pipe[1]);
        // close(right_pipe[1]);
        primes(right_pipe);
    }
    else{
        int num_temp;
        close(right_pipe[0]);
        while (1)
        {
            /* code */
            read(left_pipe[0], &num_temp, sizeof(num));
            if (num_temp % num != 0){
                write(right_pipe[1], &num_temp, sizeof(int));
            }
            if(num_temp == 0){
                break;
            } 
        }
        

    }
}


int main(){

    int right_pipe[2];
    pipe(right_pipe);

    if(fork() == 0){
        close(right_pipe[1]);
        primes(right_pipe);
    }
    else{
        int i;
        close(right_pipe[0]);
        for(i=2; i<=35; i++){
            write(right_pipe[1], &i, sizeof(int));
        }
    }
    write(right_pipe[1], 0, sizeof(int));
    return 0;
}