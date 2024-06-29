#include "CglasseFfect.h"
#include <QDebug>
CglasseFfect::CglasseFfect(QWidget* parent)
    : QWidget(parent)
{
    bgColor = new QColor(0, 0, 0,1);

}

CglasseFfect::~CglasseFfect()
{}

void CglasseFfect::setGlassBackgroundR(int R)
{
    bgColor->setRed(R);


}
void CglasseFfect::setGlassBackgroundG(int G)
{
    bgColor->setGreen(G);

}
void CglasseFfect::setGlassBackgroundB(int B)
{
    bgColor->setBlue(B);

}
void CglasseFfect::setGlassBackgroundA(int A)
{
    bgColor->setAlpha(A);

}


void CglasseFfect::paintEvent(QPaintEvent * ev)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(*bgColor);
    //painter.drawRoundedRect(rect(), 20, 20);
    painter.drawRect(0, 0, width(), height());



}
