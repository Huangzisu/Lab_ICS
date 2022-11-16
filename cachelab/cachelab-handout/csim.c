#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

// 黄子骕 21307130013

//使用 unistd.h 中的optarg
extern char* optarg;

//定义所需的结构
//line
struct line{
    int valid;
    int tag;
    int time;
};
//set
struct set{ 
    struct line* lines;
};
//cache
struct cache{
    struct set* sets;
};

//声明所需函数
int get_opt(int argc, char* argv[], int* s, int* E, int* b, char* tracefile);
void init_cache(int s, int E, int b, struct cache* cache_simulator);
//函数的实现
void init_cache(int s, int E, int b, struct cache* cache_simulator){
    int S = 2 << s;
    cache_simulator->sets = (struct cache*)malloc(S * sizeof(struct set));//为cache分配空间
    int i;
    for(i = 0;i < S; i++){
        cache_simulator->sets[i].lines = (struct line*)malloc(E * sizeof(struct line));//为每个set分配空间
        int j;
        for(j = 0;j < E; j++){
            cache_simulator->sets[i].lines[j].valid = 0;//初始化valid为0
            cache_simulator->sets[i].lines[j].tag = 0;//初始化tag为0
            cache_simulator->sets[i].lines[j].time = 0;//初始化time为0
        }
    }
    return;
}

int get_opt(int argc, char* argv[], int* s, int* E, int* b, char* tracefile){
    int option;
    while((option = getopt(argc, argv, "s:E:b:")) != -1){//判断是否检查到指定
        //swich语句，根据检查到的选项对相应参数赋值
        switch (option){
            case 's':
                *s = atoi(optarg);
                break;
            case 'E':
                *E = atoi(optarg);
                break;
            case 'b':
                *b = atoi(optarg);
                break;
            case 't':
                strcpy(tracefile, optarg);
                break;
            default:
                break;
        }
    }
    return 1;
}




int main(int argc, char* argv[])
{
    // printSummary(0, 0, 0);
    int s, E ,b;
    char* tracefile = "";
    get_opt(argc, argv, &s, &E, &b, tracefile);
    printf("%d,%d,%d", s, E, b);
    return 0;
}
