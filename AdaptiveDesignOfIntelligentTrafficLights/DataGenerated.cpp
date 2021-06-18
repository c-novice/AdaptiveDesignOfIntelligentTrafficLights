#include "Map.h"
#include <stdlib.h>

//生成数据
class DataGenerated
{
    DataGenerated(Map *myMap){
        myMap=new Map();

        int row=rand()%(10-5+1)+5;   //行，生成[5,10]个十字路口
        int col=rand()%(10-5+1)+5;   //列，生成[5,10]个十字路口
        myMap->row=row,myMap->col=col;
        int preRow=0,preCol=0;      //上一行、列

        //初始化十字路口信息
        for(int i=0;i<col;++i){
            //第一行随机生成X
            myMap->maps[0][i].centerX=preCol+rand()%(200-100+1)+100;
            preCol=myMap->maps[0][i].centerX;
        }
        for(int i=0;i<row;++i){
            //第一列随机生成Y
            myMap->maps[i][0].centerY=preRow+rand()%(200-100+1)+100;
            preRow=myMap->maps[i][0].centerY;
        }
        //其他行列直接计算
        for(int i=0;i<row;++i){
            for(int j=0;j<col;++j){
                myMap->maps[i][j].centerX=myMap->maps[0][j].centerX;
                myMap->maps[i][j].centerY=myMap->maps[i][0].centerY;
                myMap->maps[i][j].width=0;
            }
        }

        //初始化道路信息
        for(int i=0;i<row;++i){
            for(int j=0;j<col;++j){
                Road road;
                road.leftWay=road.rightWay=1;
                road.straightWay=2;

                if(j!=col-1){
                    road.length=myMap->maps[i][j+1].centerX-myMap->maps[i][j].centerX;
                    road.limitMaxSpeed=rand()%(100-80+1)+80;
                    myMap->maps[i][j].eastRoad=road;
                }
                if(j!=0){
                    road.length=myMap->maps[i][j].centerX-myMap->maps[i][j-1].centerX;
                    road.limitMaxSpeed=rand()%(100-80+1)+80;
                    myMap->maps[i][j].westRoad=road;
                }
                if(i!=row-1){
                    road.length=myMap->maps[i][j].centerY-myMap->maps[i+1][j].centerY;
                    road.limitMaxSpeed=rand()%(100-80+1)+80;
                    myMap->maps[i][j].southRoad=road;
                }
                if(i!=0){
                    road.length=myMap->maps[i][j].centerY-myMap->maps[i-1][j].centerY;
                    road.limitMaxSpeed=rand()%(100-80+1)+80;
                    myMap->maps[i][j].northRoad=road;
                }
            }
        }

        //初始化信号灯
        for(int i=0;i<row;++i){
            for(int j=0;j<col;++j){
                //信号灯时长
                myMap->maps[i][j].eastLight.redTime=rand()%(120-60+1)+60;
                myMap->maps[i][j].eastLight.greenTime=rand()%(120-60+1)+60;
                myMap->maps[i][j].eastLight.yellowTime=2;
                //信号灯状态和当前时长
                int randomState=rand()%(2-0+1)+0;
                if(randomState==0){
                    myMap->maps[i][j].eastLight.currentState=RED;
                    myMap->maps[i][j].eastLight.currentTime=rand()%(myMap->maps[i][j].eastLight.redTime);
                }else if(randomState==1){
                    myMap->maps[i][j].eastLight.currentState=YELLOW;
                    myMap->maps[i][j].eastLight.currentTime=1;
                }else{
                    myMap->maps[i][j].eastLight.currentState=GREEN;
                    myMap->maps[i][j].eastLight.currentTime=rand()%(myMap->maps[i][j].eastLight.greenTime);
                }

                //信号灯时长
                myMap->maps[i][j].westLight.redTime=rand()%(120-60+1)+60;
                myMap->maps[i][j].westLight.greenTime=rand()%(120-60+1)+60;
                myMap->maps[i][j].westLight.yellowTime=2;
                //信号灯状态和当前时长
                randomState=rand()%(2-0+1)+0;
                if(randomState==0){
                    myMap->maps[i][j].westLight.currentState=RED;
                    myMap->maps[i][j].westLight.currentTime=rand()%(myMap->maps[i][j].westLight.redTime);
                }else if(randomState==1){
                    myMap->maps[i][j].westLight.currentState=YELLOW;
                    myMap->maps[i][j].westLight.currentTime=1;
                }else{
                    myMap->maps[i][j].westLight.currentState=GREEN;
                    myMap->maps[i][j].westLight.currentTime=rand()%(myMap->maps[i][j].westLight.greenTime);
                }

                //信号灯时长
                myMap->maps[i][j].northLight.redTime=rand()%(120-60+1)+60;
                myMap->maps[i][j].northLight.greenTime=rand()%(120-60+1)+60;
                myMap->maps[i][j].northLight.yellowTime=2;
                //信号灯状态和当前时长
                randomState=rand()%(2-0+1)+0;
                if(randomState==0){
                    myMap->maps[i][j].northLight.currentState=RED;
                    myMap->maps[i][j].northLight.currentTime=rand()%(myMap->maps[i][j].northLight.redTime);
                }else if(randomState==1){
                    myMap->maps[i][j].northLight.currentState=YELLOW;
                    myMap->maps[i][j].northLight.currentTime=1;
                }else{
                    myMap->maps[i][j].northLight.currentState=GREEN;
                    myMap->maps[i][j].northLight.currentTime=rand()%(myMap->maps[i][j].northLight.greenTime);
                }

                //信号灯时长
                myMap->maps[i][j].southLight.redTime=rand()%(120-60+1)+60;
                myMap->maps[i][j].southLight.greenTime=rand()%(120-60+1)+60;
                myMap->maps[i][j].southLight.yellowTime=2;
                //信号灯状态和当前时长
                randomState=rand()%(2-0+1)+0;
                if(randomState==0){
                    myMap->maps[i][j].southLight.currentState=RED;
                    myMap->maps[i][j].southLight.currentTime=rand()%(myMap->maps[i][j].southLight.redTime);
                }else if(randomState==1){
                    myMap->maps[i][j].southLight.currentState=YELLOW;
                    myMap->maps[i][j].southLight.currentTime=1;
                }else{
                    myMap->maps[i][j].southLight.currentState=GREEN;
                    myMap->maps[i][j].southLight.currentTime=rand()%(myMap->maps[i][j].southLight.greenTime);
                }
            }
        }

    }
};
