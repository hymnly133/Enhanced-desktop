#include "ed_unit.h"
#include "mainwindow.h"
#include "qaction.h"
#include "qdebug.h"
#include "qevent.h"
#include"SysFunctions.h"
#include"ed_layout.h"
#include"ed_container.h"
#include "qgraphicseffect.h"
#include "style.h"

ED_Unit::ED_Unit(QWidget *parent,int sizex,int sizey): QWidget{parent}
{
    sizeX = sizex;
    sizeY = sizey;

    shadow_main_color = new QGraphicsDropShadowEffect;
    shadow_main_color->setBlurRadius(unit_shadow_blur_radius);   //模糊半径
    shadow_main_color->setOffset(0,0);      //偏移量
    setGraphicsEffect(shadow_main_color);

    setMainColor(QColor(88,119,144,255));
    // shadow_main_color->setEnabled(false);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction* act1  = new QAction("加宽");
    this->addAction(act1);
    connect(act1, &QAction::triggered, this, [=]()
            {
                setBlockSize(sizeX+1,sizeY);
            });

    QAction* act3  = new QAction("减宽");
    this->addAction(act3);
    connect(act3, &QAction::triggered, this, [=]()
            {
                if(sizeX>=2)
                    setBlockSize(sizeX-1,sizeY);
            });

    QAction* act2  = new QAction("加高");
    this->addAction(act2);
    connect(act2, &QAction::triggered, this, [=]()
            {
                setBlockSize(sizeX,sizeY+1);
            });



    QAction* act4  = new QAction("减高");
    this->addAction(act4);
    connect(act4, &QAction::triggered, this, [=]()
            {
                if(sizeY>=2)
                    setBlockSize(sizeX,sizeY-1);
            });



    QAction* act5  = new QAction("切换复杂度");
    this->addAction(act5);
    connect(act5, &QAction::triggered, this, [=]()
    {
        changeSimpleMode();
    });


    QAction* act6  = new QAction("删除");
    this->addAction(act6);
    connect(act6, &QAction::triggered, this, [=]()
            {
                removeFromLayout();
                deleteLater();
            });
}

void ED_Unit::single_click_action(){
    //最终单击执行

    moving = true;
    QPoint usedp = mapToGlobal(QPoint(0,0));

    if(edlayout)
        removeFromLayout();

    move(usedp);
    pMovingUnit = this;
    relativeP =cursor().pos()-pos();

}


void ED_Unit::double_click_action(){
    //最终双击执行
}

void ED_Unit::mouse_enter_action(){
    pmw->repaint();
    onmouse = true  ;
    aim_Alpha = active_alpha;
}
void ED_Unit::mouse_leave_action(){

    onmouse = false;
    aim_Alpha = sleep_alpha;
}

void ED_Unit::mouse_move_action(){
    //最终移动执行
    if (moving)
    {
        move(cursor().pos()-relativeP);
    }
    else{
    }
}

void ED_Unit::mouse_release_action(){
    //最终释放执行
    if(moving){
        //首先检查是否拖到文件夹
        ED_Layout* mwlayout = pmw->edlayout;
        QPoint point = mwlayout->NearestBlockInd(pos().x(),pos().y());
        if(!(point.x()<0||point.y()<0||point.x()>=mwlayout->row||point.y()>=mwlayout->col))
        {
            if(mwlayout->Occupied(point)){
                if(mwlayout->getUnitFromBlock(point)->type == ED_Unit::Container){
                    qDebug()<<"Container";
                    ED_Container*  c = (ED_Container*)mwlayout->getUnitFromBlock(point);
                    if(c->OKforput(this)){
                        c->InplaceAUnit(this);
                        c->raise();
                        moving = false;
                        return;
                    }
                }
            }
        }
        // 放置
                pMovingUnit = nullptr;
        mwlayout->InplaceAUnit(this);
        moving = false;

    }
}

void ED_Unit::removeFromLayout(){
    edlayout->RemoveAUnit(this);
}
void ED_Unit::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    if(event->button() == Qt::LeftButton){
        grabMouse();
        single_click_action();
    }
    repaintAround(this);
}

void ED_Unit::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    releaseMouse();
    mouse_release_action();
    repaintAround(this);
}

void ED_Unit::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    double_click_action();
}

void ED_Unit::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    mouse_move_action();
    repaintAround(this);
}

void ED_Unit::enterEvent(QEvent *event){
    event->ignore();
    mouse_enter_action();
    repaintAround(this);
}                      //进入QWidget瞬间事件
void ED_Unit::leaveEvent(QEvent *event){
    event->ignore();
    mouse_leave_action();
    repaintAround(this);
}

void ED_Unit::setBlockSize(int w,int h){
    ED_Layout* tem = nullptr;
    if(edlayout){
        tem = edlayout;
        // qDebug()<<mapToGlobal(QPoint(0,0));
        removeFromLayout();
        // qDebug()<<mapToGlobal(QPoint(0,0));

        ED_Unit temu(nullptr,w,h);
        if(tem->OKforput(&temu)){
            sizeX = w;
            sizeY = h;
        }
        tem->InplaceAUnit(this);
    }
    else{
        sizeX = w;
        sizeY = h;
    }

}

void ED_Unit::getaClick( ){
    single_click_action();
}

void ED_Unit::getaDoubleClick( ){
    double_click_action();
}

void ED_Unit::update_after_resize(){
}

void ED_Unit::setSimpleMode(bool val){
    simpleMode = val;
    whenSimpleModeChange(val);
}

void ED_Unit::changeSimpleMode(){
    setSimpleMode(!simpleMode);
}

void ED_Unit::whenSimpleModeChange(bool val){}

void ED_Unit::whenScaleChange(float val){}

void ED_Unit::setScale(float val){
    scale = val;
    whenScaleChange(val);
}

void ED_Unit::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    paintSide(this,QColor("green"));
    paintRect(this,mainColor_Alphaed());
}

void ED_Unit::setMainColor(QColor color){
    mainColor = color;
    auto tem = color;
    tem.setAlpha(unit_shadow_alpha);
    shadow_main_color->setColor(tem);
    shadow_main_color->update();
}
QColor ED_Unit::mainColor_Alphaed(){
    QColor tem = mainColor;
    tem.setAlpha(aim_Alpha);
    return tem;
}
