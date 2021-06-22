#ifndef CAR_H
#define CAR_H

#endif // CAR_H
#include "Road.h"

//车辆
class Car
{
public:
    int length;         //车长
    int speed;          //车速
    Orientation currentHead;      //朝向

    Road currentRoad;       //当前所在的道路
    int minDistance;        //与前一辆车保持的最小间距
    int preDistance;        //与前一辆车的当前距离
    int remainDistance;     //距离下一个十字路口还有的距离
    int currentState;       //0代表执行，1代表左转，2代表右转
};
