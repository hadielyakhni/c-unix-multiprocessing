#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int words_count = atoi(argv[1]);
    int sc = sizeof(char), si = sizeof(int);
    for(int i = 2; i < 2 + words_count; i+=2){
        int c1c2[2], c2c1[2];
        pipe(c1c2);
        pipe(c2c1);
        if(!fork()){
            char *my_word = argv[i];
            int my_wrod_length = strlen(my_word);
            int my_pid = getpid(), bro_pid, bro_word_length;
            write(c1c2[1], &my_pid, si);
            write(c1c2[1], &my_wrod_length, si);
            write(c1c2[1], my_word, strlen(my_word) * sc);
            read(c2c1[0], &bro_pid, si);
            read(c2c1[0], &bro_word_length, si);
            char bro_word[bro_word_length];
            read(c2c1[0], bro_word, (bro_word_length + 1) * sc);
            printf("I am child number %d of pid %d, I have received from my brother %d of pid %d the word %s\n", i-1, my_pid, i, bro_pid, bro_word);
            exit(0);
        }
        if(!fork()){
            char *my_word = argv[i + 1];
            int my_wrod_length = strlen(my_word);
            int my_pid = getpid(), bro_pid, bro_word_length;
            read(c1c2[0], &bro_pid, si);
            read(c1c2[0], &bro_word_length, si);
            char bro_word[bro_word_length];
            read(c1c2[0], bro_word, (bro_word_length + 1) * sc);
            printf("I am child number %d of pid %d, I have received from my brother %d of pid %d the word %s\n", i, my_pid, i-1, bro_pid, bro_word);
            write(c2c1[1], &my_pid, si);
            write(c2c1[1], &my_wrod_length, si);
            write(c2c1[1], my_word, strlen(my_word) * sc);
            exit(0);
        }
    }
    return 0;
}
