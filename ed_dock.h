#ifndef ED_DOCK_H
#define ED_DOCK_H

#include "ed_container.h"
#include "ed_unit.h"
#include <QWidget>
#include"ed_layout.h"

class ED_Dock : public ED_Container
{
    Q_OBJECT
public:
    explicit ED_Dock(QWidget *parent,int outSizeX,int outSizeY,int inSize);
    int insize;
    virtual void InplaceAUnit(ED_Unit* aim) override;
    virtual bool OKforput(ED_Unit* aim) override;

    void paintEvent(QPaintEvent *event);
signals:
};

#endif // ED_DOCK_H
