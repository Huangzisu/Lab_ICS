#include <stdio.h>
#include <unistd.h>

extern char* optarg;

struct test
{
    int a;
};


int main(int argc, char* argv[]){
    struct test* ok = (struct test*)malloc(3*sizeof(struct test));
}