#include "ed_bgshower.h"
#include "mainwindow.h"
#include "qgraphicseffect.h"
#include "qpainter.h"

ed_bgShower::ed_bgShower(QWidget *parent)
    : QWidget{parent}
{
    QGraphicsBlurEffect* ef = new QGraphicsBlurEffect(this);
    ef->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
    ef->setEnabled(true);
    ef->setBlurRadius(10);
    setGraphicsEffect(ef);

}
void ed_bgShower::paintEvent(QPaintEvent * ev){
    QPainter painter(this);
    QRegion tem = pmw->edlayout->region;
    if(pMovingUnit) tem = tem.united(pMovingUnit->geometry());
    painter.setClipRegion(tem);
    painter.drawPixmap(rect(),*pbg);
    // update();
}
