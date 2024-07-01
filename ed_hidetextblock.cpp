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
    dark =true;
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


    auto tem = mainColor;
    tem.setAlpha(icon_shadow_alpha);
    QGraphicsDropShadowEffect* effect0 = new QGraphicsDropShadowEffect;
    effect0->setColor(tem);
    effect0->setBlurRadius(icon_shadow_blur_radius);   // 模糊半径
    effect0->setOffset(0);      // 偏移量
    lb->setGraphicsEffect(effect0);

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

