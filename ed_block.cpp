#include "ed_block.h"
#include "QWidget"
#include "qboxlayout.h"
#include "qgraphicsview.h"
#include "qlabel.h"

ED_BLOCK::ED_BLOCK(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* vl = new QVBoxLayout();

    QGraphicsView* gv = new QGraphicsView();
    QLabel* lb = new QLabel();
    vl->addWidget(gv);
    vl->addWidget(lb);
    lb->setAlignment(Qt::AlignCenter);
    lb->setText("Icon");
    setMinimumSize(100 ,100);
    setMaximumSize(100,100);
    setLayout(vl);
}
