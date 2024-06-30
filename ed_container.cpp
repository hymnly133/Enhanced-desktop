#include "ed_container.h"
#include "qdebug.h"
#include"SysFunctions.h"

ED_Container::ED_Container(QWidget *parent, int sizex, int sizey,int row,int cal,int space,int space_x,int space_y)
    : ED_Unit(parent,sizex,sizey),row(row),cal(cal),space(space)
{
    int temx,temy;
    type = Container;
    if(space_x == 0)
         temx = space;
    else temx = space_x;

    if(space_y ==0)
        temy = space;
    else temy = space_y;
    edlayout = new ED_Layout(this,row,cal,space,temx,temy);
}
void ED_Container::paintEvent(QPaintEvent *event){
    paintRect(this,QColor(255,255,255,aim_Alpha));
    Q_UNUSED(event);
}

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
void ED_Container::setSimpleMode(bool val){
    ED_Unit::setSimpleMode(val);
    for(ED_Unit* content:*(edlayout->contents)){
        content->setSimpleMode(val);
    }
}

void ED_Container::setScale(float val){
    ED_Unit::setScale(val);
    for(ED_Unit* content:*(edlayout->contents)){
        content->setScale(val);
    }
}


void ED_Container::update_after_resize(){
    edlayout->Update_Positon();
}
