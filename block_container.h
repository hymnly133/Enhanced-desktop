#ifndef BLOCK_CONTAINER_H
#define BLOCK_CONTAINER_H

#include <QWidget>
#include"ed_layout.h"

class Block_Container : public ED_Unit
{
    Q_OBJECT
public:
    explicit Block_Container(QWidget *parent,int sizex,int sizey);
    ED_Layout* edlayout;
    void InitLayout(int row,int cal,int space);
    void Say();

protected:
    void double_click_action();
    void single_click_action();
    void paintEvent(QPaintEvent *event);
    // void mouseMoveEvent(QMouseEvent *event) override;

};


#endif // BLOCK_CONTAINER_H
