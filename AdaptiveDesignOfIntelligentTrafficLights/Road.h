#ifndef ROAD_H
#define ROAD_H

#endif // ROAD_H

#include <vector>
#include "Car.h"

//朝向
enum Orientation
{
    NORTH,
    SOUTH,
    WEST,
    EAST
};

//道路
class Road
{
public:
    double length;             //道路长
    int limitMaxSpeed;         //道路限速
    int straightWay;           //直行道数量
    int leftWay;               //左转道数量
    int rightWay;              //右转道数量
    bool isBlocked;            //是否处于拥堵状态
    Orientation orientation;   //朝向
    std::vector<Car>cars;      //该道路上的车

public:
    bool operator==(const Road r){
        if(length!=r.length)return false;
        if(limitMaxSpeed!=r.limitMaxSpeed)return false;
        if(straightWay!=r.straightWay)return false;
        if(leftWay!=r.leftWay)return false;
        if(rightWay!=r.rightWay)return false;
        if(isBlocked!=r.isBlocked)return false;
        if(orientation!=r.orientation)return false;

        return true;
    }
};
