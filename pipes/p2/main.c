#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 

int main(int argc, char const *argv[])
{
    int n;
    n = fork();
    n = n -fork();
    printf("le resultat de %d est %d\n", fork(), n);
    return 0;
}
