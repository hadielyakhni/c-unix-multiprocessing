#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int 
        lowest = 0, 
        highest = 1000, 
        target = 1,
        one = 3,
        minus_one = -1,
        zero = 0,
        si = sizeof(int);
    int pc[2], cp[2];
    pipe(pc);
    pipe(cp);
    if(!fork()){
        int current = 500, iterations = 1;
        while(1){
            int response;
            write(cp[1], &current, si);
            read(pc[0], &response, si);
            if(response == 0){
                printf("Number found: %d, after %d iterations\n", target, iterations);
                kill(getppid(), 9);
                exit(0);
            }
            if(response == 1) lowest = current;
            if(response == -1) highest = current;
            current = (lowest + highest) / 2;
            printf("current guess: %d\n", current);
            iterations++;
        }
    }
    int guess;
    while(1){
        read(cp[0], &guess, si);
        if(target == guess) write(pc[1], &zero, si);
        if(target < guess) write(pc[1], &minus_one, si);
        if(target > guess) write(pc[1], &one, si);
    }   
    return 0;
}
