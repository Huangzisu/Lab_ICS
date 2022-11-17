#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

// 黄子骕 21307130013

//使用 unistd.h 中的optarg
extern char* optarg;
//定义全局变量
int miss = 0;
int hit = 0;
int eviction = 0;

//定义所需的结构
//line
struct line{
    int valid;
    int tag;
    int time;//用来记录距离上一次使用过去了几次操作
};
//set
struct set{ 
    struct line* lines;
};
//cache
struct cache{
    struct set* sets;
    int set_size;
    int set_num;
};

//声明所需函数
int get_opt(int argc, char* argv[], int* s, int* E, int* b, char* tracefile);//得到命令行参数
void init_cache(int s, int E, int b, struct cache* cache_simulator);//初始化cache
int get_set_index(int addr, int s, int b);//返回set_index值
int get_tag(int addr, int s, int b);//返回tag值
int test_miss(struct cache* cache_simulator, int set_index, int tag);//检查是否miss，miss返回1，hit返回0
int find_victim(struct cache* cache_simulator, int set_index);//根据LRU replacement policy查找替换的line，返回该line的index
void data_load(struct cache* cache_simulator, int set_index, int tag);//进行data load操作
int test_full(struct cache* cache_simulator, int set_index);//检查指定set是否装满，若满则返回1，若不满则返回0
void update_time(struct cache* cache_simulator, int set_index, int tag);//更新指定set中的所有line的time，将最新操作的line的time置为0
void data_store(struct cache* cache_simulator, int set_index, int tag);//进行data store操作，在本实验中与load操作所需做变化相同
void data_modify(struct cache* cache_simulator, int set_index, int tag);//进行data modify操作，在本实验中即先load操作，后store操作

//函数的实现
void data_modify(struct cache* cache_simulator, int set_index, int tag){
    data_load(cache_simulator, set_index, tag);
    data_store(cache_simulator, set_index, tag);
    return;
}

void data_store(struct cache* cache_simulator, int set_index, int tag){
    data_load(cache_simulator, set_index, tag);
    return;
}

void data_load(struct cache* cache_simulator, int set_index, int tag){
    //先判断是否miss
    if(test_miss(cache_simulator, set_index, tag)){//miss的情况
        miss++;
        //检查是否装满
        if(test_full(cache_simulator, set_index)){
            //若装满表明发生eviction
            eviction++;
            //修改victim的状态
            int victim_index = find_victim(cache_simulator, set_index);
            cache_simulator->sets[set_index].lines[victim_index].valid = 1;
            cache_simulator->sets[set_index].lines[victim_index].tag = tag;            
        }else{//若不满
            int i;
            for(i = 0; i < cache_simulator->set_size; i++){
                if(cache_simulator->sets[set_index].lines[i].valid == 0){//找到空位并修改指定line的状态
                    cache_simulator->sets[set_index].lines[i].valid = 1;
                    cache_simulator->sets[set_index].lines[i].tag = tag;
                    break;
                }
            }
        }  
    }else{//hit的情况
        hit++;
    }
    //更新set中所有line的time
    update_time(cache_simulator, set_index, tag);
    return;
}

void update_time(struct cache* cache_simulator, int set_index, int tag){
    int i;
    for(i = 0; i < cache_simulator->set_size; i++){
        if(cache_simulator->sets[set_index].lines[i].tag == tag){
            cache_simulator->sets[set_index].lines[i].time = 0;
        }else{
            cache_simulator->sets[set_index].lines[i].time++;
        }
    }
}

int test_full(struct cache* cache_simulator, int set_index){
    int i;
    for(i = 0; i < cache_simulator->set_size; i++){
        if(cache_simulator->sets[set_index].lines[i].valid == 0){
            return 0;
        }
    }
    return 1;
}

int find_victim(struct cache* cache_simulator, int set_index){
    int i;
    int max_time_index = 0;
    for(i = 0; i < cache_simulator->set_size; i++){
        if(cache_simulator->sets[set_index].lines[i].time > cache_simulator->sets[set_index].lines[max_time_index].time){
            max_time_index = i;
        }
    }
    return max_time_index;
}

int test_miss(struct cache* cache_simulator, int set_index, int tag){
    int i;
    for(i = 0; i < cache_simulator->set_size; i++){
        if(cache_simulator->sets[set_index].lines[i].valid == 1 && cache_simulator->sets[set_index].lines[i].tag == tag){
            return 0;
        }
    }
    return 1;
}

int get_tag(int addr, int s, int b){
    return addr >> (s + b);
}

int get_set_index(int addr, int s, int b){
    int mask = (1 << s) - 1;
    return (addr >> b) & mask;
}

void init_cache(int s, int E, int b, struct cache* cache_simulator){
    int S = 2 << s;
    cache_simulator->set_size = E;
    cache_simulator->set_num = S;
    cache_simulator->sets = (struct set*)malloc(S * sizeof(struct set));//为cache分配空间
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
    while((option = getopt(argc, argv, "s:E:b:t:")) != -1){//判断是否检查到指定
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
    int s, E, b;
    char file_name[100];
    //读取参数
    get_opt(argc, argv, &s, &E, &b, file_name);
    //初始化cache_simulator
    struct cache cache_simulator;
    init_cache(s, E, b, &cache_simulator);
    //读取并根据指令操作
    FILE *tracefile;
    tracefile = fopen(file_name, "r");
    char instruction;
    int addr;
    int size;//无需考虑但是还是保存一下
    while(fscanf(tracefile, "%c %x,%d", &instruction, &addr, &size) != EOF){
        //得到set_index和tag值
        int set_index = get_set_index(addr, s, b);
        int tag = get_tag(addr, s, b);
        //判断指令
        switch (instruction)
        {
        case 'L':
            data_load(&cache_simulator, set_index, tag);
            break;
        case 'S':
            data_store(&cache_simulator, set_index, tag);
            break;
        case 'M':
            data_modify(&cache_simulator, set_index, tag);
        default://为'I'的情况，不做处理
            break;
        } 
    }
    printSummary(hit, miss, eviction);    
    return 0;
}
