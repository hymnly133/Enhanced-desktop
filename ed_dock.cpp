#include "ed_dock.h"
#include "SysFunctions.h"
#include"ed_unit.h"
#include "qdebug.h"
#include"QPainterPath"
#include"QPainter"
ED_Dock::ED_Dock(QWidget *parent,int outSizeX,int outSizeY,int inSize)
    : ED_Container(parent,outSizeX,outSizeY,inSize,1,20,50,20)
{
    alwaysShow = true;
    insize = inSize;
}

void ED_Dock::InplaceAUnit(ED_Unit* aim){
    aim->setBlockSize(1,1);
    edlayout->InplaceAUnit(aim);
}

bool ED_Dock::OKforput(ED_Unit* aim){
    ED_Unit tem(nullptr,1,1);
    qDebug()<<edlayout->col;
    return edlayout->OKforput(&tem);
}

void ED_Dock::paintEvent(QPaintEvent *event){
    paintRect(this,QColor(0,0,155,aim_Alpha));
    paintLight(this,QColor(0,0,155,aim_Alpha));
    // QPainter p(this);
    // p.setRenderHint(QPainter::Antialiasing);
    // QPainterPath path;
    // path.addRoundedRect(QRectF(rect()), 10, 10);


    // p.setPen(Qt::NoPen);
    // p.fillPath(path, QColor(0,0,155,aim_Alpha));
    // p.drawPath(path);
}
