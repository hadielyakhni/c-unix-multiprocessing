#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    char p1[sizeof(char)*3] = "P1", p2[sizeof(char)*3] = "P2";
    int si = sizeof(int);
    
    mkfifo("pp1", 0777);
    mkfifo("p1p", 0777);
    mkfifo("pp2", 0777);
    mkfifo("p2p", 0777);

    int pp1 = open("pp1", O_RDWR);
    int p1p = open("p1p", O_RDWR);
    int pp2 = open("pp2", O_RDWR);
    int p2p = open("p2p", O_RDWR);

    while (1){
        char target_process[sizeof(char)*3];
        int value, response;
        printf("Target Process (P1 or P2)? ");
        scanf("%s", target_process);
        printf("Enter a value: ");
        scanf("%d", &value);
        if(strcmp(target_process, p1) == 0){
            write(pp1, &value, si);
            read(p1p, &response, si);
            if(response!=-1)
                printf("p1 value: %d\n", response);
            else {
                printf("p1 cannot update its value.. value above limit or below 0\n");
                printf("p2 will take care of that!\n");
                write(pp2, &value, si);
                read(p2p, &response, si);
                if(response!=-1)
                    printf("p2 value: %d\n", response);
                else {
                    printf("p2 cannot update its value.. value above limit or below 0\n");
                    printf("try other values..\n");
                }
            }
        }
        else if(strcmp(target_process, p2) == 0){
            write(pp2, &value, si);
            read(p2p, &response, si);
            if(response!=-1)
                printf("p2 value: %d\n", response);
            else {
                printf("p2 cannot update its value.. value above limit or below 0\n");
                printf("p1 will take care of that!\n");
                write(pp1, &value, si);
                read(p1p, &response, si);
                if(response!=-1)
                    printf("p1 value: %d\n", response);
                else {
                    printf("p1 cannot update its value.. value above limit or below 0\n");
                    printf("try other values..\n");
                }
            }
        }
        else {
            printf("error\n");
        }
    }
    

    return 0;
}
