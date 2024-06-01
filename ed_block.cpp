#include "ed_block.h"
#include "QWidget"
#include"QProcess"
#include "qboxlayout.h"
#include"SysFunctions.h"
#include "qlabel.h"
#include"QDebug"
#include"QUrl"
#include"QDesktopServices"
#include"QTextCodec"
#include "qpainter.h"
#include"QGraphicsDropShadowEffect"
int ED_BLOCK::default_size = 48;
ED_BLOCK::ED_BLOCK(QWidget *parent, QImage image, QString _name, QString _cmd, int sizex, int sizey)
    : ED_Unit(parent,sizex,sizey)
{
    type =Block;
    cmd = _cmd;
    cmd = QString("file:///")+cmd;
    name = _name;
    // 初始化内部组件
    vl = new QVBoxLayout();
    vl->setContentsMargins(5,0,5,0);
    vl->addSpacing(0);


    gv = new PictureBox(this,1.0);

    lb = new QLabel();
    lb->adjustSize();
    // lb->setMaximumHeight(20);

    // 显示图标
    gv->setMode(PictureBox::FIX_SIZE_CENTRED);
    double defaultRatio = (double)default_size/image.size().width();
    // qDebug()<<defaultRatio;
    gv->setImage(image,1.0,defaultRatio);
    gv->setBackground(QBrush (QColor(0,0,0,0)));

    // gv->QWidget::setAlignment(Qt::AlignVCenter);


    // 绑定事件
    connect(gv,SIGNAL(sendaClick()),this,SLOT(getaClick()));
    connect(gv,SIGNAL(sendaDoubleClick()),this,SLOT(getaDoubleClick()));

    // 添加布局
    vl->addWidget(gv);
    vl->setAlignment(gv,Qt::AlignHCenter);
    vl->addWidget(lb);
    vl->setAlignment(lb,Qt::AlignHCenter);

    // 显示名字
    lb->setAlignment(Qt::AlignHCenter);
    lb->setFont(QFont("MiSans",10,40));
    lb->setFixedWidth(width()-5);

    lb->setText(elidedLineText(lb,3,name));
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor(100,100,100,100));
    effect->setBlurRadius(2);   //模糊半径
    effect->setOffset(10);      //偏移量
    lb->setGraphicsEffect(effect);

    gv->setGraphicsEffect(effect);

    setLayout(vl);
}
void ED_BLOCK::single_click_action(){
    //最终单击执行
    ED_Unit::single_click_action();
        // qDebug("BLOCK-single_click_action");
}

void ED_BLOCK::double_click_action(){
    //最终双击执行
    ED_Unit::double_click_action();
    qDebug("cmd = %s",qPrintable(cmd));
    QDesktopServices::openUrl(QUrl(cmd));
    // qDebug("BLOCK-double_click_action");
}

void ED_BLOCK::getaClick( ){
    single_click_action();
}

void ED_BLOCK::getaDoubleClick( ){
    double_click_action();
}
void ED_BLOCK::update_after_resize(){
    lb->setFixedWidth(width()-5);
    lb->setText(elidedLineText(lb,3,name));
}

void ED_BLOCK::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(QColor("green")); //设置画笔记颜色
    p.drawRect(0, 0, width() -1, height() -1); //绘制边框
}
