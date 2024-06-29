#include "ed_bgshower.h"
#include "mainwindow.h"
#include "qgraphicseffect.h"
#include "qpainter.h"
#include "QDebug"

ed_bgShower::ed_bgShower(QWidget *parent)
    : QWidget{parent}
{
    QGraphicsBlurEffect* ef = new QGraphicsBlurEffect(this);
    ef->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
    ef->setEnabled(true);
    ef->setBlurRadius(20);
    setGraphicsEffect(ef);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
}
void ed_bgShower::paintEvent(QPaintEvent * ev){
    QPainter painter(this);
    auto tem = updateMask();
    painter.setClipRegion(tem);
    painter.drawPixmap(rect(),pmw->bg);
}

QRegion ed_bgShower::updateMask(){
    QRegion tem = pmw->edlayout->region;
    if(pMovingUnit){
        auto pos = pMovingUnit->mapToGlobal(QPoint(0,0));
        auto geo = pMovingUnit->geometry();
         tem = tem.united(QRect(pos.x(),pos.y(),geo.width(),geo.height()));
    }

    // setMask(tem);
    return tem;
}
