#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int max = atoi(argv[1]);
    int 
        current_value = 0,
        new_value,
        si = sizeof(int),
        minus_one = -1;

    int pp1 = open("pp1", O_RDWR);
    int p1p = open("p1p", O_RDWR);

    while(1){
        read(pp1, &new_value, si);
        if(current_value + new_value >= 0 && current_value + new_value <= max){
            current_value += new_value;
            printf("p1: %d\n", current_value);
            write(p1p, &current_value, si);
        }
        else
            write(p1p, &minus_one, si);
    }

    return 0;
}
