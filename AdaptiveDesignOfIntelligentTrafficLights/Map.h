#ifndef MAP_H
#define MAP_H

#endif // MAP_H
#include <vector>
#include "Crossroads.h"
#include "Car.h"

class Map
{
public:
    const static int maxn=20;
    int row,col;    //行、列数
    Crossroads maps[maxn][maxn];        //由十字路口组成的二维地图
    std::vector<Car>cars;               //当前地图的所有车

public:
    Light searchLightByRoad(Car car);       //查询该车辆面对的信号灯
    void changeRoad(Car car,int remainDistance);    //改变当前车辆的道路
    void refreshAllLights();      //更新所有的信号灯
    void runOneSecond();          //模拟1s的运行结果
    void calResult();             //计算一次完整的模拟过程的过程信息
};
