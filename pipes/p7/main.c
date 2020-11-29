#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    char *file_name = "io_file";

    if (fork() == 0)
    {
        int fd = open(file_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 1);  //refirects output to io_file
        close(fd);
        execlp("ls","ls", "-al", NULL);    
    } //child
    else {
        wait(NULL);
        int fd = open(file_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 0);  //refirects input from io_file
        close(fd);
        execlp("wc","wc", "-l", NULL);
    } //parent
    return 0;
}
