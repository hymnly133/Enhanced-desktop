#include "ed_unit.h"
#include "qpainter.h"

ED_Unit::ED_Unit(QWidget *parent,int sizex,int sizey): QWidget{parent}
{
    sizeX = sizex;
    sizeY = sizey;
}

void ED_Unit::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    single_click_action();
}

void ED_Unit::single_click_action(){
    //最终单击执行

    qDebug("Unit-single_click_action");
    emit sendSelf(this);
}

void ED_Unit::double_click_action(){

    qDebug("Unit-double_click_action");
}

void ED_Unit::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    // double_click_action();
}

void ED_Unit::getaClick( ){
    single_click_action();
}

void ED_Unit::getaDoubleClick( ){
    double_click_action();
}

void ED_Unit::update_after_resize(){}
void ED_Unit::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(QColor("green")); //设置画笔记颜色
    p.drawRect(0, 0, width() -1, height() -1); //绘制边框
}
