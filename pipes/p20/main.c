#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    int a = atoi(argv[1]), b = atoi(argv[2]);
    int p[2];
    pipe(p);
    
    if(!fork()){
        int sum = 0;
        for (int i = a; i <= (a+b)/2; i++) sum += i;
        write(p[1], &sum, sizeof(int));
        exit(0);
    }

    if(!fork()){
        int sum = 0;
        for (int i = (a+b)/2 + 1; i <= b; i++) sum += i;
        write(p[1], &sum, sizeof(int));
        exit(0);
    }

    int sum1, sum2;
    read(p[0], &sum1, sizeof(int));
    read(p[0], &sum2, sizeof(int));
    printf("sigma a b = %d\n", sum1 + sum2);

    return 0;
}
