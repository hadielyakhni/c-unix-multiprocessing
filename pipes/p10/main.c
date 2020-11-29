#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 

int main() {

    int pc[2], cp[2], one = 1, si = sizeof(int);
    pipe(pc);
    pipe(cp);

    if(fork()){
        while (1) {
            printf("Ping\n");
            write(pc[1], &one, si);
            read(cp[0], &one, si);
        }
    } //parent
    else {
        while(1) {
            read(pc[0], &one, si);
            printf("Pong\n");
            sleep(1);
            write(cp[1], &one, si);
        }
    } //child

    return 0;
}