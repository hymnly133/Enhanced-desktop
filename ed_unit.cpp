#include "ed_unit.h"
#include "mainwindow.h"
#include "qdebug.h"
#include "qevent.h"
#include"SysFunctions.h"
#include"ed_layout.h"
#include"ed_container.h"
#include "style.h"

ED_Unit::ED_Unit(QWidget *parent,int sizex,int sizey): QWidget{parent}
{
    sizeX = sizex;
    sizeY = sizey;
    moving = false;
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
    //最终移动执行
    aim_Alpha = active_alpha;
}
void ED_Unit::mouse_leave_action(){
    //最终移动执行
    aim_Alpha = sleep_alpha;
}
void ED_Unit::setwinblur(){
    // setWindowFlags( Qt::Window | Qt::FramelessWindowHint);
    // setWindowState(Qt::WindowFullScreen);
    // setAttribute(Qt::WA_TranslucentBackground);//背景半透明属性设置   //窗口透明
    // HWND hWnd = HWND(this->winId());
    // HMODULE hUser = GetModuleHandle(L"user32.dll");
    // if (hUser)
    // {
    //     pfnSetWindowCompositionAttribute setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");
    //     if (setWindowCompositionAttribute)
    //     {
    //         ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0xf2f230, 0, 0 };
    //         WINDOWCOMPOSITIONATTRIBDATA data;
    //         data.Attrib = WCA_ACCENT_POLICY;
    //         data.pvData = &accent;
    //         data.cbData = sizeof(accent);
    //         setWindowCompositionAttribute(hWnd, &data);
    //     }
    // }
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
    if(val) changeToSimpleMode();
    else changeToComplexMode();
}

void ED_Unit::changeSimpleMode(){
    setSimpleMode(!simpleMode);
}

void ED_Unit::changeToSimpleMode(){}
void ED_Unit::changeToComplexMode(){}

void ED_Unit::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    paintSide(this,QColor("green"));
    paintRect(this,QColor(100,0,0,20));
}
