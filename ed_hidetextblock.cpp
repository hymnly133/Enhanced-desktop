#include "ed_hidetextblock.h"
#include "qdebug.h"
#include "qgraphicseffect.h"
#include "SysFunctions.h"
#include "qpainter.h"
#include "qurl.h"
#include"QDesktopServices"

int ED_HideTextBlock::default_size = 48;
ED_HideTextBlock::ED_HideTextBlock(QWidget *parent,QPixmap image,QString _name,QString _cmd,int sizex,int sizey)
    :ED_Unit(parent,sizex,sizey)
{
    type =Unit;
    cmd = _cmd;
    cmd = QString("file:///")+cmd;
    name = _name;

    setMainColor(pixmapMainColor(image,sleep_color_ratio));
    // 初始化内部组件

    gv = new PictureBox(this,1.0);

    lb = new QLabel();
    lb->adjustSize();
    // lb->setMaximumHeight(20);

    // 显示图标
    gv->setMode(PictureBox::FIX_SIZE_CENTRED);
    double defaultRatio = (double)default_size/image.size().width();
    qDebug()<<defaultRatio;
    gv->setImage(image,1.0,1);
    gv->setBackground(QBrush (QColor(0,0,0,0)));
    gv->setMode(PictureBox::AUTO_ZOOM);

    // gv->QWidget::setAlignment(Qt::AlignVCenter);

    // 显示名字
    // lb->setAlignment(Qt::AlignHCenter);
    // lb->setFont(QFont("MiSans",10,40));
    // lb->setFixedWidth(width()-5);

    // lb->setText(elidedLineText(lb,3,name));
    // QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    // effect->setColor(QColor(100,100,100,100));
    // effect->setBlurRadius(2);   //模糊半径
    // effect->setOffset(10);      //偏移量
    // lb->setGraphicsEffect(effect);

    // gv->setGraphicsEffect(effect);
}
void ED_HideTextBlock::single_click_action(){
    //最终单击执行
    ED_Unit::single_click_action();
    qDebug("BLOCK-single_click_action");
}

void ED_HideTextBlock::double_click_action(){
    //最终双击执行
    ED_Unit::double_click_action();
    qDebug("cmd = %s",qPrintable(cmd));
    QDesktopServices::openUrl(QUrl(cmd));
    qDebug("BLOCK-double_click_action");
}



void ED_HideTextBlock::getaClick( ){
    single_click_action();
}

void ED_HideTextBlock::getaDoubleClick( ){
    double_click_action();
}
void ED_HideTextBlock::update_after_resize(){
    lb->setFixedWidth(width()-5);
    lb->setText(elidedLineText(lb,3,name));
    gv->setFixedSize(rect().size());
}

void ED_HideTextBlock::paintEvent(QPaintEvent *event)
{
    ED_Unit::paintEvent(event);
}

