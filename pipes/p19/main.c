#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    int childs_count = atoi(argv[1]);
    if(!childs_count){
        printf("Program terminated - childs count not valid!\n");
        exit(0);
    }
    int si = sizeof(int), zero = 0;
    int pipes[childs_count][2];
    for(int i=0; i<childs_count; i++){
        pipe(pipes[i]);
    }
    for(int i = 0; i < childs_count; i++){
        if(!fork()){
            int pid = getpid(), result;
            if(i==0){  //first child
                write(pipes[i][1], &pid, si);
            }
            else {
                read(pipes[i-1][0], &result, si);
                result += pid;
                write(pipes[i][1], &result, si);
            }
            exit(0);
        }
    }
    int total_pid_sum;
    read(pipes[childs_count - 1][0], &total_pid_sum, si);
    total_pid_sum += getpid();
    printf("childs + parent pids sum is %d\n", total_pid_sum);
    return 0;
}
