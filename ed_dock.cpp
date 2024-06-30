#include "ed_dock.h"
#include "SysFunctions.h"
#include"ed_unit.h"
#include "qdebug.h"
#include"QPainterPath"
#include"QPainter"
ED_Dock::ED_Dock(QWidget *parent,int outSizeX,int outSizeY,int inSize)
    : ED_Container(parent,outSizeX,outSizeY,inSize,1,2,80,10)
{
    alwaysShow = true;
    insize = inSize;
    setMainColor(QColor(79,98,124));
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
    // paintRect(this,QColor(0,0,155,aim_Alpha));



    QPainter painter(this);
    QLinearGradient linearGradient(QPoint(0,0),QPoint(width(),0));

    auto tem = mainColor;
    tem.setAlpha(aim_Alpha);


    paintLight(this,tem);
    linearGradient.setColorAt(0, tem);

    linearGradient.setColorAt(1, tem);

    for(int i=0;i<insize;i++){
        if(edlayout->Occupied(i,0)){
            auto temm = edlayout->getUnitFromBlock(i,0)->mainColor;
            float ratio = 1.0*edlayout->blocks[i][0]->CenterX()/width();
            // qDebug()<<"found" << i<<ratio<<edlayout->blocks[i][0]->CenterX()<<width();
            temm.setAlpha(aim_Alpha);
            linearGradient.setColorAt(ratio, temm);
        }
    }


    // 使用线性渐变创建一个画刷，用来填充
    QBrush brush(linearGradient);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    // x, y, w, h
    painter.drawRect(rect());


    // QPainter p(this);
    // p.setRenderHint(QPainter::Antialiasing);
    // QPainterPath path;
    // path.addRoundedRect(QRectF(rect()), 10, 10);


    // p.setPen(Qt::NoPen);
    // p.fillPath(path, QColor(0,0,155,aim_Alpha));
    // p.drawPath(path);
}
