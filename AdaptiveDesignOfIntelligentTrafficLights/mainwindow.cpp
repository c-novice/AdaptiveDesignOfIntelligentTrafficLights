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

