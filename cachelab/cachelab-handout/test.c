#include <stdio.h>
#include <unistd.h>

extern char* optarg;

struct test
{
    int a;
};


int main(int argc, char* argv[]){
    printf("%d", 61 % 10);
}