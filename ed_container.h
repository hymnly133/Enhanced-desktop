#ifndef ED_CONTAINER_H
#define ED_CONTAINER_H

#include <QWidget>
#include"ed_layout.h"

class ED_Container : public ED_Unit
{
    Q_OBJECT
public:
    explicit ED_Container(QWidget *parent,int sizex,int sizey,int row,int cal,int space,int space_x =0,int space_y = 0);
    ED_Layout* edlayout;
    int row,cal,space;
    // virtual void InitLayout();
    void Say();
    virtual void InplaceAUnit(ED_Unit* aim);
    virtual bool OKforput(ED_Unit* aim);
    virtual void changeToSimpleMode();
    virtual void changeToComplexMode();
protected:
    void double_click_action();
    void single_click_action();
    void paintEvent(QPaintEvent *event);
};


#endif // ED_CONTAINER_H
