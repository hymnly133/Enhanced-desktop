#include "block_container.h"
#include "qpainter.h"

Block_Container::Block_Container(QWidget *parent)
    : ED_Unit(parent,2,2)
{
    type = Container;

}
void Block_Container::paintEvent(QPaintEvent *event){

    QPainter paint(this);
    paint.setPen(Qt::blue);
    paint.fillRect(rect(), QBrush(QColor(10,10,10,100)));
}
void Block_Container::double_click_action(){
    ED_Unit::double_click_action();

}
void Block_Container::single_click_action(){
    ED_Unit::single_click_action();
}
void Block_Container::InitLayout(int row,int cal,int space){
        edlayout = new ED_Layout(this,row,cal,space);
}
