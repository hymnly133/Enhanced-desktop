#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"SysFunctions.h"
#include <QMouseEvent>
#include <QDebug>
#include<QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_test_pushButton_clicked()
{
    qDebug()<<"clicked";
}


// void MainWindow::mousePressEvent(QMouseEvent *event)
// {
//     // 如果是鼠标左键按下
//     if(event->button() == Qt::LeftButton)
//     {
//         qDebug("left");
//     }
//     // 如果是鼠标右键按下
//     else if(event->button() == Qt::RightButton)
//     {
//                qDebug("right");
//     }
// }
