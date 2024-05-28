#include "ed_block.h"
#include "QWidget"
#include "qboxlayout.h"
#include "qgraphicsview.h"
#include "qlabel.h"

ED_BLOCK::ED_BLOCK(QWidget *parent)
    : QWidget{parent}
{
    vl = new QVBoxLayout();
    gv = new PictureBox();
    lb = new QLabel();
    QImage image("qrc:/images/testicon");
    gv->setImage(image);



    connect(gv,SIGNAL(sendaclick()),this,SLOT(getformGV()));

    vl->addWidget(gv);
    vl->addWidget(lb);
    lb->setAlignment(Qt::AlignCenter);
    lb->setText("Icon");
    setMinimumSize(100 ,100);
    setMaximumSize(100,100);
    setLayout(vl);
}

void ED_BLOCK::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug("BLOCK-press");
    emit sendSelf(this);                                  //信号发送该控件地址
}
void ED_BLOCK::getformGV( ){
    emit sendSelf(this);
}
