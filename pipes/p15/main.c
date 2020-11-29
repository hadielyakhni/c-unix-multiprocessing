#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    int limit = atoi(argv[1]);
    int si = sizeof(int);
    int pc[2], cp[2];
    pipe(pc);
    pipe(cp);
    if(!fork()){
        srand (time(NULL));
        int iterations = 1;
        while(1){
            int nb = rand() % limit;
            int parent_nb, zero=0, one=1;
            read(pc[0], &parent_nb, si);
            if (nb == parent_nb && iterations > 1){
                printf("Child:\tafter %d iterations. Number: %d\n", iterations, nb);
                write(cp[1], &one, si);
                exit(0);
            }
            else {
                write(cp[1], &zero, si);
            }
            iterations++;
        }
    }
    int iterations = 1;
    while(1){
        srand (time(NULL));
        int nb = rand() % limit;
        int status;
        write(pc[1], &nb, si);
        read(cp[0], &status, si);
        if(status == 1){
            printf("Parent:\tafter %d iterations. Number: %d\n", iterations, nb);
            exit(0);
        }
        iterations++;
    }
    return 0;
}
