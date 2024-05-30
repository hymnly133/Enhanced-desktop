#ifndef ED_UNIT_H
#define ED_UNIT_H

#include "ed_layout.h"
#include <QWidget>

class ED_Unit : public QWidget
{
    Q_OBJECT
public:
    enum ED_TYPE {Unit,Block,Container};
    ED_TYPE type = Unit;
    int sizeX;
    int sizeY;
    int LayoutBlockX = -1;
    int LayoutBlockY = -1;
    ED_Layout* playout;
    explicit ED_Unit(QWidget *parent, ED_Layout* layout);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    virtual void double_click_action();
    virtual void single_click_action();
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
signals:
    void sendSelf(ED_Unit *self);
public slots:
    void getaClick();
    void getaDoubleClick();
};


#endif // ED_UNIT_H
