#include "ed_container.h"
#include "qdebug.h"
#include "qpainter.h"

ED_Container::ED_Container(QWidget *parent, int sizex, int sizey,int row,int cal,int space)
    : ED_Unit(parent,sizex,sizey),row(row),cal(cal),space(space)
{
    type = Container;
    edlayout = new ED_Layout(this,row,cal,space,space,space);
}
void ED_Container::paintEvent(QPaintEvent *event){
    QPainter paint(this);
    paint.setPen(Qt::blue);
    paint.fillRect(rect(), QBrush(QColor(10,10,10,50)));
    Q_UNUSED(event);
}
void ED_Container::double_click_action(){
    ED_Unit::double_click_action();

}
void ED_Container::single_click_action(){
    ED_Unit::single_click_action();
}
// void ED_Container::InitLayout(){
//     edlayout = new ED_Layout(this,row,cal,space);
// }
void ED_Container::Say(){
    for(ED_Unit* content:*(edlayout->contents)){
        qDebug()<<content->pos()<<content->mapToGlobal(content->pos())<<content->size()<<"X,Y"<<content->LayoutBlockX<<content->LayoutBlockY;
    }
}

void ED_Container::InplaceAUnit(ED_Unit* aim){
    edlayout->InplaceAUnit(aim);
}
bool ED_Container::OKforput(ED_Unit* aim){
    return edlayout->OKforput(aim);
}
