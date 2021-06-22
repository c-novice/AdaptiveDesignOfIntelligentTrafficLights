#ifndef PSO_H
#define PSO_H
#include "Map.h"
#include"stdlib.h"
#include"time.h"
#include"math.h"

#define randf ((rand()%10000+rand()%10000*10000)/100000000.0) //产生-1随机浮点数

const int NUM=40;//粒子数
const int DIM=30;//维数
constexpr double c1=1.8;//参数
constexpr double c2=1.8;//参数
constexpr double xmin=-100.0;//位置下限
constexpr double xmax=100.0;//位置上限
double gbestx[DIM];//全局最优位置
double gbestf;//全局最优适应度

struct particle {//定义一个粒子
    double x[DIM];//当前位置矢量
    double bestx[DIM];//历史最优位置
    double f;//当前适应度
    double bestf;//历史最优适应度
}swarm[NUM];//定义粒子群

class PSO
{
public:

public:
    PSO();
    PSO(Map* map){
        myMap=map;
    }
    Map *myMap;

    //搜索目标解
    double run();
};

#endif // PSO_H
