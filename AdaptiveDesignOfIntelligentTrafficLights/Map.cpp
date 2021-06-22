#include "Map.h"

Light  Map::searchLightByRoad(Car car)
{
    Road road=car.currentRoad;
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j){
            if(road==maps[i][j].eastRoad&&car.currentHead==WEST){
                return maps[i][j].eastLight;
            }else if(road==maps[i][j].westRoad&&car.currentHead==EAST){
                return maps[i][j].westLight;
            }else if(road==maps[i][j].southRoad&&car.currentHead==NORTH){
                return maps[i][j].southLight;
            }else if(road==maps[i][j].northRoad&&car.currentHead==SOUTH){
                return maps[i][j].northLight;
            }
        }
    }
    return Light();
}

void Map::changeRoad(Car car, int remainDistance)
{
    Road road=car.currentRoad;
    //先确定进入的十字路口
    Crossroads tmp;
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j){
            if(maps[i][j].eastRoad==road&&road.orientation==WEST){
                tmp=maps[i][j];
                break;
            }else if(maps[i][j].westRoad==road&&road.orientation==EAST){
                tmp=maps[i][j];
                break;
            }else if(maps[i][j].southRoad==road&&road.orientation==NORTH){
                tmp=maps[i][j];
                break;
            }else if(maps[i][j].northRoad==road&&road.orientation==SOUTH){
                tmp=maps[i][j];
                break;
            }
        }
    }

    //切换道路
    if(car.currentState==0){    //直行
        if(road.orientation==EAST){
            car.currentRoad=tmp.eastRoad;
        }else if(road.orientation==WEST){
            car.currentRoad=tmp.westRoad;
        }else if(road.orientation==SOUTH){
            car.currentRoad=tmp.southRoad;
        }else if(road.orientation==NORTH){
            car.currentRoad=tmp.northRoad;
        }

    }else if(car.currentState==1){
        if(road.orientation==EAST){
            car.currentRoad=tmp.northRoad;
        }else if(road.orientation==WEST){
            car.currentRoad=tmp.southRoad;
        }else if(road.orientation==SOUTH){
            car.currentRoad=tmp.eastRoad;
        }else if(road.orientation==NORTH){
            car.currentRoad=tmp.westRoad;
        }

    }else if(car.currentState==2){
        if(road.orientation==EAST){
            car.currentRoad=tmp.southRoad;
        }else if(road.orientation==WEST){
            car.currentRoad=tmp.northRoad;
        }else if(road.orientation==SOUTH){
            car.currentRoad=tmp.westRoad;
        }else if(road.orientation==NORTH){
            car.currentRoad=tmp.eastRoad;
        }
    }

    //确定道路后，尝试继续向前进
    //获取当前道路的信号灯
    Light currentLight=searchLightByRoad(car);
    //case1：当前道路为红灯
    if(currentLight.currentState==RED){
        //1、考虑到十字路口的限制
        int tmp=std::min(car.remainDistance,car.remainDistance);
        //2、考虑前一辆车的限制
        tmp=std::min(tmp,std::min(car.remainDistance,car.preDistance-car.minDistance));

        car.remainDistance-=tmp;    //更新和十字路口的距离
        //查找该道路上的前一辆车
        Car preCar;
        for(int i=0;i<car.currentRoad.cars.size();++i){
            preCar=car.currentRoad.cars[i];
            if(preCar.remainDistance>=car.remainDistance)
                break;
        }
        //计算与前一辆车的间距
        car.preDistance=car.remainDistance-preCar.remainDistance;
    }else{
        //判断是否可以出道路
        if(car.remainDistance<=car.remainDistance){
            //该车切换道路
            changeRoad(car,car.remainDistance-car.remainDistance);
        }else{
            //只是前进，相对距离不变
            car.remainDistance-=car.remainDistance;
        }
    }

}

void Map::refreshAllLights()
{
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j){
            Light tmp=maps[i][j].eastLight;
            tmp.currentTime++;
            if(tmp.currentState==RED&&tmp.currentTime==tmp.redTime){
                tmp.currentTime=0;
                tmp.currentState=GREEN;
            }else if(tmp.currentState==GREEN&&tmp.currentTime==tmp.greenTime){
                tmp.currentTime=0;
                tmp.currentState=YELLOW;
            }else if(tmp.currentState==YELLOW&&tmp.currentTime==tmp.yellowTime){
                tmp.currentTime=0;
                tmp.currentState=RED;
            }
            maps[i][j].eastLight=tmp;

            tmp=maps[i][j].westLight;
            tmp.currentTime++;
            if(tmp.currentState==RED&&tmp.currentTime==tmp.redTime){
                tmp.currentTime=0;
                tmp.currentState=GREEN;
            }else if(tmp.currentState==GREEN&&tmp.currentTime==tmp.greenTime){
                tmp.currentTime=0;
                tmp.currentState=YELLOW;
            }else if(tmp.currentState==YELLOW&&tmp.currentTime==tmp.yellowTime){
                tmp.currentTime=0;
                tmp.currentState=RED;
            }
            maps[i][j].westLight=tmp;

            tmp=maps[i][j].northLight;
            tmp.currentTime++;
            if(tmp.currentState==RED&&tmp.currentTime==tmp.redTime){
                tmp.currentTime=0;
                tmp.currentState=GREEN;
            }else if(tmp.currentState==GREEN&&tmp.currentTime==tmp.greenTime){
                tmp.currentTime=0;
                tmp.currentState=YELLOW;
            }else if(tmp.currentState==YELLOW&&tmp.currentTime==tmp.yellowTime){
                tmp.currentTime=0;
                tmp.currentState=RED;
            }
            maps[i][j].northLight=tmp;

            tmp=maps[i][j].southLight;
            tmp.currentTime++;
            if(tmp.currentState==RED&&tmp.currentTime==tmp.redTime){
                tmp.currentTime=0;
                tmp.currentState=GREEN;
            }else if(tmp.currentState==GREEN&&tmp.currentTime==tmp.greenTime){
                tmp.currentTime=0;
                tmp.currentState=YELLOW;
            }else if(tmp.currentState==YELLOW&&tmp.currentTime==tmp.yellowTime){
                tmp.currentTime=0;
                tmp.currentState=RED;
            }
            maps[i][j].southLight=tmp;
        }
    }
}

void Map::runOneSecond()
{
    //所有的车辆根据信号灯模拟
    for(Car car:cars){
        //获取当前道路的信号灯
        Light currentLight=searchLightByRoad(car);
        //case1：当前道路为红灯
        if(currentLight.currentState==RED){
            //1、考虑到十字路口的限制
            int tmp=std::min(car.remainDistance,car.speed);
            //2、考虑前一辆车的限制
            tmp=std::min(tmp,std::min(car.speed,car.preDistance-car.minDistance));

            car.remainDistance-=tmp;    //更新和十字路口的距离
            //查找该道路上的前一辆车
            Car preCar;
            for(int i=0;i<car.currentRoad.cars.size();++i){
                preCar=car.currentRoad.cars[i];
                if(preCar.remainDistance>=car.remainDistance)
                    break;
            }
            //计算与前一辆车的间距
            car.preDistance=car.remainDistance-preCar.remainDistance;
        }else{
            //判断是否可以出道路
            if(car.remainDistance<=car.speed){
                //该车切换道路
                changeRoad(car,car.speed-car.remainDistance);
            }else{
                //只是前进，相对距离不变
                car.remainDistance-=car.speed;
            }
        }
    }

    //更新所有的信号灯
    refreshAllLights();
}


