#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QtWin>
#include <QPainter>

class CglasseFfect  : public QWidget
{
    Q_OBJECT

public:
    CglasseFfect(QWidget*parent);

    ~CglasseFfect();
    void setGlassBackgroundR(int R);
    void setGlassBackgroundG(int G);
    void setGlassBackgroundB(int B);
    void setGlassBackgroundA(int A);
    void paintEvent(QPaintEvent* ev);


private:
    QColor*bgColor = nullptr;

};


