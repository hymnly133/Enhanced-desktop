#include "block_container.h"
#include "qpainter.h"

Block_Container::Block_Container(QWidget *parent)
    : ED_Unit(parent,2,2)
{
    type = Container;
    inside_layout = new ED_Layout(this,3,3,3);
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
void Block_Container::AddAUnit(ED_Unit* aim,QPoint ind){
    aim->setParent(this);
    inside_layout->put_ED_Unit(aim,ind);
    for(int i=0;i<20;i++){
        if(!contents[i]){
            contents[i] = aim;
        }
    }
    aim->update_after_resize();
}
