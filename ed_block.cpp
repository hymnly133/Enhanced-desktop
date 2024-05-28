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
    QImage image;

    image.load(":/images/testicon");

    gv->setImage(image,0.5);
    gv->setBackground(QBrush (QColor(0,0,0,0)));
    gv->setMode(PictureBox::AUTO_ZOOM);



    connect(gv,SIGNAL(sendaClick()),this,SLOT(getaClick()));
    connect(gv,SIGNAL(sendaDoubleClick()),this,SLOT(getaDoubleClick()));

    vl->addWidget(gv);
    vl->addWidget(lb);
    lb->setAlignment(Qt::AlignCenter);
    lb->setText("Icon");
    setMinimumSize(100 ,100);
    setMaximumSize(100,100);
    setLayout(vl);
}
void ED_BLOCK::single_click_action(){
        qDebug("BLOCK-single_click_action");
    emit sendSelf(this);
}

void ED_BLOCK::double_click_action(){
    qDebug("BLOCK-double_click_action");
}


void ED_BLOCK::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    single_click_action();                                //信号发送该控件地址
}
void ED_BLOCK::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    double_click_action();                                //信号发送该控件地址
}


void ED_BLOCK::getaClick( ){
    single_click_action();
}

void ED_BLOCK::getaDoubleClick( ){
    double_click_action();
}
