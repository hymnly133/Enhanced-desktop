#include "mainwindow.h"
#include "block_container.h"
#include "ed_block.h"
#include "qpainter.h"
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

    Init(this);
    // ui->groupBox->setStyleSheet("QGroupBox {border: 0;}");

    // // 设置边框颜色和宽度为0，相当于隐藏边框：
    // ui->groupBox->setStyleSheet("QGroupBox {border: 0px solid transparent;}");

    edlayout = new ED_Layout(this,20,20,5);

    QList<FileInfo> icons = scanalldesktopfiles();

    for(int i=0;i<icons.size();i++){
        qDebug()<<icons[i].filePath;
        cd[i] = new ED_BLOCK(this,icons[i].icon.pixmap(256).toImage(),icons[i].name,icons[i].filePath);
        InitAUnit(cd[i]);
        iconNum++;
    }


    bc = new Block_Container(this);
    InitAUnit(bc);

}
void MainWindow::InitAUnit(ED_Unit* aim){
    switch(aim->type){
    case ED_Unit::Block:
        connect(aim, &ED_BLOCK::sendSelf, this, &MainWindow::getObject);
        break;
    case ED_Unit::Unit:
        connect(aim, &ED_Unit::sendSelf, this, &MainWindow::getObject);
    case ED_Unit::Container:
        connect(aim, &Block_Container::sendSelf, this, &MainWindow::getObject);
    }
    int w= aim->sizeX*edlayout->W_Block-2*edlayout->space;
    int h= aim->sizeY*edlayout->H_Block-2*edlayout->space;
    setFixedSize(w,h);
    edlayout->add_ED_Unit(aim);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getObject(ED_Unit *w)
{
    // 收到小部件的点击信号，移动初始化
    moving = true;
    temp = w;
    edlayout->RemoveAUnit(w);
    startP = cursor().pos() - this->pos();
    yuanP = temp->pos();
    /*将此小部件提升到父小部件堆栈的顶部*/
    temp->raise();


}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // 小部件移动
    if (moving)
        if (temp)
            temp->move(yuanP.x() + event->x() - startP.x(), yuanP.y() + event->y() - startP.y());
}

// 拖拽对象置顶，卡牌积压的时候，拖动的那张卡牌置顶
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(moving){
        // 遍历各个点位寻找最小差异的位置
        QPoint block = edlayout->NearestEmptyBlockInd(temp,temp->pos().x(),temp->pos().y());
        edlayout->put_ED_Unit(temp,block.x(),block.y());
        temp->raise();
        moving = false;
    }
}


void MainWindow::setIconScale(double scale){
    for(int i=0;i<iconNum;i++){
        if(cd[i]->type == ED_Unit::Block){
            ED_BLOCK* p = (ED_BLOCK*)cd[i];
            p->gv->setScale(scale);
        }
    }
}

void MainWindow::setIconHight(int val){
    for(int i=0;i<iconNum;i++){
        if(cd[i]->type == ED_Unit::Block){
            ED_BLOCK* p = (ED_BLOCK*)cd[i];
            p->vl->setSpacing(val);
        }
    }
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    setIconScale((double)value/50);
}


void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    setIconHight(value);
}


void MainWindow::paintEvent(QPaintEvent * ev)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/images/background"),QRect());
}
