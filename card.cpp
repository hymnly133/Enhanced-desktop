#include "card.h"

card::card(QWidget *parent):QWidget(parent)
{
    this->setGeometry(0,0,200,400);       //设置控件窗口大小
}

card::~card()
{

}

void card::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);                               //创建画笔
    painter.setRenderHint(QPainter::Antialiasing,true);
    QBrush brush;                                         //创建笔刷
    brush.setColor(Qt::yellow);                           //设置笔刷颜色
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);                              //设置画笔笔刷
    painter.drawRoundedRect(QRectF(5,5,190,390),10,10);   //绘制圆角矩形并填充
}

void card::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug("card-press");
    emit sendSelf(this);                                  //信号发送该控件地址
}
