#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DataGenerated.cpp"

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

    }

    //case1：当前道路为红灯

    //距离足够继续前进
    //距离不足继续前进

    //case2：当前道路为绿灯

    //前一道路不拥堵，当前道路拥堵
    //前一道路不拥堵，当前道路不拥堵
    //前一道路拥堵，当前道路拥堵
    //前一道路拥堵，当前道路不拥堵

        //更新所有信号灯
}

