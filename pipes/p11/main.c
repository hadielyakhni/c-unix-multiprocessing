#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int numbers[] = {atoi(argv[1]), atoi(argv[2]), atoi(argv[3])};

    int pc1[2], c1c2[2], c2c3[2], c3p[2], si = sizeof(int);
    pipe(pc1); pipe(c1c2); pipe(c2c3); pipe(c3p);

    if(!fork()){
        int nb1, nb2, nb3, pid=getpid();
        read(pc1[0], &nb1, si);
        read(pc1[0], &nb2, si);
        read(pc1[0], &nb3, si);
        printf("Iam the child 1 of pid %d, I've received from my parent of pid %d the right to start\n", getpid(), getppid());
        write(c1c2[1], &pid, si);
        write(c1c2[1], &nb1, si);
        write(c1c2[1], &nb2, si);
        write(c1c2[1], &nb3, si);
    }
    else {
        if(!fork()){
            int nb1, nb2, nb3, pid=getpid(), bother_pid;
            read(c1c2[0], &bother_pid, si);
            read(c1c2[0], &nb1, si);
            read(c1c2[0], &nb2, si);
            read(c1c2[0], &nb3, si);
            printf("Iam the child 2 of pid %d, I've received from my brother of pid %d the number %d\n", getpid(), bother_pid, nb1);
            write(c2c3[1], &pid, si);
            write(c2c3[1], &nb2, si);
            write(c2c3[1], &nb3, si);
        }
        else {
            if(!fork()){
                int nb2, nb3, pid=getpid(), bother_pid;
                read(c2c3[0], &bother_pid, si);
                read(c2c3[0], &nb2, si);
                read(c2c3[0], &nb3, si);
                printf("Iam the child 3 of pid %d, I've received from my brother of pid %d the number %d\n", getpid(), bother_pid, nb2);
                write(c3p[1], &pid, si);
                write(c3p[1], &nb3, si);
            }
            else {
                int nb3, c3_pid;
                write(pc1[1], &numbers[0], si);
                write(pc1[1], &numbers[1], si);
                write(pc1[1], &numbers[2], si);
                read(c3p[0], &c3_pid, si);
                read(c3p[0], &nb3, si);
                printf("Iam the parent of pid %d, I've received from my child of pid %d the number %d\n", getpid(), c3_pid, nb3);
            }
        }
    }

    return 0;
}
