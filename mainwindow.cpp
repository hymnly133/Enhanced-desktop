#include "mainwindow.h"
#include "ed_block.h"
#include "ui_mainwindow.h"
#include "SysFunctions.h"
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置无边框窗口
    Init(this);

    int maxrow = 5;
    int nowicon = 0;
    int allicons = 22;
    // ui->Icons_layout->addWidget(mled);

    for (int i = 0; i < allicons; i++)
    {
        ED_BLOCK *tem = new ED_BLOCK();
        ui->Icons_layout->addWidget(tem, nowicon % maxrow, nowicon / maxrow);
        nowicon++;
    }

    ui->groupBox->setStyleSheet("QGroupBox {border: 0;}");

    // 设置边框颜色和宽度为0，相当于隐藏边框：
    ui->groupBox->setStyleSheet("QGroupBox {border: 0px solid transparent;}");

    for (int i = 0; i < 8; i++)
    {
        cd[i] = new ED_BLOCK(this);
        connect(cd[i], &ED_BLOCK::sendSelf, this, &MainWindow::getObject);
        cd[i]->move(i % 4 * 200, i / 4 * 400 + 20);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_test_pushButton_clicked()
{
    qDebug() << "clicked";
}
void MainWindow::getObject(ED_BLOCK *w)
{
    // 收到小部件的点击信号，移动初始化
    moving = true;
    temp = w;
    startP = cursor().pos() - this->pos();
    yuanP = temp->pos();
    /*将此小部件提升到父小部件堆栈的顶部*/
    temp->raise();
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // 小部件移动
    qDebug("mw-moving");
    if (moving)
        if (temp)
            temp->move(yuanP.x() + event->x() - startP.x(), yuanP.y() + event->y() - startP.y());
}

// 拖拽对象置顶，卡牌积压的时候，拖动的那张卡牌置顶
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug("mw-releasse");
    int dtwidth = 2560;
    int dtheight = 1440;
    int mindeltaX = dtwidth;
    int mindeltaY = dtheight;
    int bpx, bpy;
    // 遍历各个点位寻找最小差异的位置
    for (int j = 0; j < 10; j++)
    {
        int deltaY = abs(temp->pos().y() - 144 * j);
        if (deltaY < mindeltaY)
        {
            mindeltaY = deltaY;
            bpy = 144 * j;
        }
    }
    for (int j = 0; j < 22; j++)
    {
        int deltaX = abs(temp->pos().x() - 115 * j);
        if (deltaX < mindeltaX)
        {
            mindeltaX = deltaX;
            bpx = 115 * j;
        }
    }
    temp->move(bpx, bpy);
    temp->raise();
    moving = false;
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
