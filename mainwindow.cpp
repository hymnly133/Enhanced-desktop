#include "mainwindow.h"
#include "block_container.h"
#include "ed_block.h"
#include "qpainter.h"
#include "ui_mainwindow.h"
#include "SysFunctions.h"
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Init(this);

    edlayout = new ED_Layout(this,15,10,5);


    QList<FileInfo> iconns = scanalldesktopfiles();

    for(int i=0;i<iconns.size();i++){
        qDebug()<<iconns[i].filePath;
        auto tem = new ED_BLOCK(this,iconns[i].icon.pixmap(256).toImage(),iconns[i].name,iconns[i].filePath);
        InitAUnit(tem);
        tem->raise();
    }

    auto bc = new Block_Container(this,6,6);
    InitAUnit(bc);
    bc->InitLayout(5,5,3);

}
void MainWindow::InitAUnit(ED_Unit* aim){
    connect(aim, &ED_Unit::sendSelf, this, &MainWindow::getObject);
    edlayout->InitAUnit(aim);
    aim->ind = iconNum;
    iconNum++;

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
    w->removeFromLayout();
    w->setParent(this);
    w->setVisible(true);
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
        //首先检查是否拖到文件夹
        QPoint point = edlayout->NearestBlockInd(temp->pos().x(),temp->pos().y());
        if(edlayout->Occupied(point)){
            if(edlayout->getUnitFromBlock(point)->type == ED_Unit::Container){
                qDebug()<<"Container";
                Block_Container*  c = (Block_Container*)edlayout->getUnitFromBlock(point);
                if(c->edlayout->OKforput(temp)){
                    c->edlayout->InplaceAUnit(temp);
                    c->raise();
                    temp->raise();
                    moving = false;
                    return;
                }
            }
        }
        // 放置
        edlayout->InplaceAUnit(temp);
        temp->raise();
        moving = false;
    }
}


void MainWindow::setIconScale(double scale){
    for(ED_Unit* content:*(edlayout->contents)){
        if(content->type == ED_Unit::Block){
            ED_BLOCK* p = (ED_BLOCK*)content;
            p->gv->setScale(scale);
        }
    }
}

void MainWindow::setIconHight(int val){
    for(ED_Unit* content:*(edlayout->contents)){
        if(content->type == ED_Unit::Block){
            ED_BLOCK* p = (ED_BLOCK*)content;
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
