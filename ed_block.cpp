#include "ed_block.h"
#include "QWidget"
#include "qboxlayout.h"
#include "qlabel.h"

ED_BLOCK::ED_BLOCK(QWidget *parent)
    : QWidget{parent}
{
    // 初始化内部组件
    vl = new QVBoxLayout();
    gv = new PictureBox();
    lb = new QLabel();

    // 显示图标
    QImage image;
    image.load(":/images/testicon");

    gv->setImage(image,0.5);
    gv->setBackground(QBrush (QColor(0,0,0,0)));
    gv->setMode(PictureBox::AUTO_ZOOM);

    // 绑定事件
    connect(gv,SIGNAL(sendaClick()),this,SLOT(getaClick()));
    connect(gv,SIGNAL(sendaDoubleClick()),this,SLOT(getaDoubleClick()));

    // 添加布局
    vl->addWidget(gv);
    vl->addWidget(lb);
    lb->setAlignment(Qt::AlignCenter);
    lb->setText("Icon");
    setMinimumSize(100 ,100);
    setMaximumSize(100,100);
    setLayout(vl);
}
void ED_BLOCK::single_click_action(){
    //最终单击执行

        qDebug("BLOCK-single_click_action");
    emit sendSelf(this);
}

void ED_BLOCK::double_click_action(){
    //最终双击执行

    qDebug("BLOCK-double_click_action");
}



//以下为鼠标事件传递
void ED_BLOCK::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    single_click_action();
}
void ED_BLOCK::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    double_click_action();
}

void ED_BLOCK::getaClick( ){
    single_click_action();
}

void ED_BLOCK::getaDoubleClick( ){
    double_click_action();
}
