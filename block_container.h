#ifndef BLOCK_CONTAINER_H
#define BLOCK_CONTAINER_H

#include "ed_block.h"
#include <QWidget>
#include"ed_layout.h"

class Block_Container : public ED_Unit
{
    Q_OBJECT
public:
    explicit Block_Container(QWidget *parent = nullptr);
    ED_Layout* edlayout;
    void InitLayout(int row,int cal,int space);

protected:
    void double_click_action();
    void single_click_action();
    void paintEvent(QPaintEvent *event) override;


// signals:
//     void sendSelf(ED_BLOCK *self);
// public slots:
//     void getaClick();
//     void getaDoubleClick();
};


#endif // BLOCK_CONTAINER_H
