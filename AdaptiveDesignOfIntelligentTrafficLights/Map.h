#ifndef MAP_H
#define MAP_H

#endif // MAP_H
#include <vector>
#include "Crossroads.h"

class Map
{
public:
    const static int maxn=20;
    int row,col;    //行、列数
    Crossroads maps[maxn][maxn];        //由十字路口组成的二维地图
};
