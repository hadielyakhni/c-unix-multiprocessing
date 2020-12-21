#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int sec = atoi(argv[1]);
    while (1)
    {
        if(sec == 0){
            printf("Fin\n");
            break;
        }
        printf("%d\n", sec);    
        sleep(1);
        sec--;
    }
    return 0;
}
