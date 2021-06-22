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
