#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DataGenerated.cpp"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    new DataGenerated(myMap);   //生成数据


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::runOneSecond()
{
    //所有的车辆根据信号灯模拟
    for(Car car:myMap->cars){
        //获取当前道路的信号灯
        Light currentLight=myMap->searchLightByRoad(car);
        //case1：当前道路为红灯
        if(currentLight.currentState==RED){
            //1、考虑到十字路口的限制
            int tmp=std::min(car.remainDistance,car.speed);
            //2、考虑前一辆车的限制
            tmp=std::min(tmp,std::min(car.speed,car.preDistance-car.minDistance));

            car.remainDistance-=tmp;    //更新和十字路口的距离
        }else{
            //判断是否可以出道路
            if(car.remainDistance<=car.speed){
                //该车切换道路
                myMap->changeRoad(car,car.speed-car.remainDistance);
            }else{
                //只是前进
                car.remainDistance-=car.speed;
            }
        }
    }

    //更新所有的信号灯
    myMap->refreshAllLights();
}

