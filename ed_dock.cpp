#include "ed_dock.h"
#include"ed_unit.h"
#include "qdebug.h"
#include "qpainter.h"
#include "SysFunctions.h"
ED_Dock::ED_Dock(QWidget *parent,int outSize,int inSize)
    : ED_Container(parent,outSize,1,inSize,1,3,20,20)
{
    alwaysShow = true;
    insize = inSize;
}

void ED_Dock::InplaceAUnit(ED_Unit* aim){
    qDebug()<<"dock inplayce";
    aim->setBlockSize(1,1);
    edlayout->InplaceAUnit(aim);
}

bool ED_Dock::OKforput(ED_Unit* aim){
        qDebug()<<"dock ok";
    ED_Unit tem(nullptr,1,1);
    if(edlayout) qDebug()<<"dock edlayout exit";
    else qDebug()<<"dock edlayout bad";
    qDebug()<<edlayout->col;
    return edlayout->OKforput(&tem);
}

void ED_Dock::paintEvent(QPaintEvent *event){
    paintRect(this,QColor(0,0,155,20));
}
