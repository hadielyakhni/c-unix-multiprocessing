#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{

    if(!fork()){
        execlp("ps", "ps", "-aux", NULL);
    }
    else {
        wait(NULL);
        if(!fork()){
            execlp("ls", "ls", "-al", NULL);
        }
        else{
            wait(NULL);
            execlp("ipcs", "ipcs", NULL);
        }
    }
    return 0;
}
