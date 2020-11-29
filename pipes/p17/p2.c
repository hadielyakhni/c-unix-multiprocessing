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

    int pp2 = open("pp2", O_RDWR);
    int p2p = open("p2p", O_RDWR);

    while(1){
        read(pp2, &new_value, si);
        if(current_value + new_value >= 0 && current_value + new_value <= max){
            current_value += new_value;
            printf("p2: %d\n", current_value);
            write(p2p, &current_value, si);
        }
        else
            write(p2p, &minus_one, si);
    }

    return 0;
}
