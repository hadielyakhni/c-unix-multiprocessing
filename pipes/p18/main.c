#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <time.h>

int isPrime(int nb) {
    for (int i = 2; i <= nb / 2; ++i) 
        if (nb % i == 0) return 0;
    return 1;
}

int main(int argc, char const *argv[])
{
    int childs_count = atoi(argv[1]);
    int upper_limit = atoi(argv[2]);
    int in[2], out[2], si = sizeof(int), total_finished = 0, minus_one = -1;
    pipe(in);
    pipe(out);
    if(!fork()){
        for(int i = 2; i <= upper_limit; i++){
            write(in[1], &i, si);
        } 
        for(int i = 0; i < childs_count; i++){
            write(in[1], &minus_one, si);
        } 
        exit(0);
    }
    for(int i = 0; i < childs_count; i++){
        if(!fork()){
            while(1){
                int nb;
                read(in[0], &nb, si);
                if(nb == minus_one){
                    write(out[1], &nb, si);
                    exit(0);
                }
                if(isPrime(nb)) 
                    write(out[1], &nb, si);
            }
        }
    }
    while (total_finished < childs_count){
        int prime;
        read(out[0], &prime, si);
        if(prime == minus_one){
            total_finished++;
            continue;
        }
        printf("%d\n", prime);
    }
    return 0;
}
