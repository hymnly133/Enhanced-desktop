#include "ed_unit.h"
#include "mainwindow.h"
#include "qdebug.h"
#include "qevent.h"
#include"SysFunctions.h"
#include"ed_layout.h"
#include"ed_container.h"
#include<QtWinExtras>

ED_Unit::ED_Unit(QWidget *parent,int sizex,int sizey): QWidget{parent}
{
    alwaysShow = false;
    sizeX = sizex;
    sizeY = sizey;
    // setMouseTracking(true);
    moving = false;
    bgshower = new QLabel(this);
    // 创建QBlurEffect并设置模糊半径
    // 将模糊效果应用于QLabel上
}




void ED_Unit::single_click_action(){
    //最终单击执行

    moving = true;
    QPoint usedp = mapToGlobal(QPoint(0,0));

    if(edlayout)
        removeFromLayout();

    move(usedp);
    pMovingUnit = this;
    relativeP =cursor().pos()-pos();

}

void ED_Unit::double_click_action(){
    //最终双击执行
}

void ED_Unit::mouse_move_action(){
    //最终移动执行
    if (moving)
    {
        move(cursor().pos()-relativeP);
        // qDebug("NormalMove");
        // qDebug()<<int(type);
    }
    else{
        // qDebug("NoMoving");
    }
}

void ED_Unit::mouse_release_action(){
    //最终释放执行
    if(moving){
        //首先检查是否拖到文件夹
        ED_Layout* mwlayout = pmw->edlayout;
        QPoint point = mwlayout->NearestBlockInd(pos().x(),pos().y());
        if(mwlayout->Occupied(point)){
            if(mwlayout->getUnitFromBlock(point)->type == ED_Unit::Container){
                qDebug()<<"Container";
                ED_Container*  c = (ED_Container*)mwlayout->getUnitFromBlock(point);
                if(c->OKforput(this)){
                    c->InplaceAUnit(this);
                    c->raise();
                    this->raise();
                    moving = false;
                    return;
                }
            }
        }
        // 放置
        mwlayout->InplaceAUnit(this);
        this->raise();
        moving = false;
        pMovingUnit = nullptr;
    }
}

void ED_Unit::removeFromLayout(){
    edlayout->RemoveAUnit(this);
}
void ED_Unit::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    if(event->button() == Qt::LeftButton){
        grabMouse();
        single_click_action();
    }

}

void ED_Unit::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    releaseMouse();
    mouse_release_action();

}

void ED_Unit::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    double_click_action();
}

void ED_Unit::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    mouse_move_action();
}

void ED_Unit::setBlockSize(int w,int h){
    ED_Layout* tem = nullptr;
    if(edlayout){
        tem = edlayout;
        // qDebug()<<mapToGlobal(QPoint(0,0));
        removeFromLayout();
        // qDebug()<<mapToGlobal(QPoint(0,0));

        ED_Unit temu(nullptr,w,h);
        if(tem->OKforput(&temu)){
            sizeX = w;
            sizeY = h;
        }
        tem->InplaceAUnit(this);
    }
    else{
        sizeX = w;
        sizeY = h;
    }




}

void ED_Unit::getaClick( ){
    single_click_action();
}

void ED_Unit::getaDoubleClick( ){
    double_click_action();
}

void ED_Unit::update_after_resize(){
    bgshower->setFixedSize(width(),height());
}
void ED_Unit::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
        // 创建QLabel并设置背景图片
    paintside(this,QColor("green"));
}
