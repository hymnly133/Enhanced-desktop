#include "ed_bgshower.h"
#include "mainwindow.h"
#include "qgraphicseffect.h"
#include "qpainter.h"
#include "QDebug"

ed_bgShower::ed_bgShower(QWidget *parent)
    : QWidget{parent}
{
    // QGraphicsBlurEffect* ef = new QGraphicsBlurEffect(this);
    // ef->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
    // ef->setEnabled(true);
    // ef->setBlurRadius(20);
    // setGraphicsEffect(ef);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);//背景半透明属性设置   //窗口透明
    setwinblur();
}
void ed_bgShower::setwinblur(){
    HWND hWnd = HWND(this->winId());
    HMODULE hUser = GetModuleHandle(L"user32.dll");
    if (hUser)
    {
        pfnSetWindowCompositionAttribute setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");
        if (setWindowCompositionAttribute)
        {
            ACCENT_POLICY accent = { ACCENT_ENABLE_ACRYLICBLURBEHIND, 0xf2f230, 0, 0 };
            WINDOWCOMPOSITIONATTRIBDATA data;
            data.Attrib = WCA_ACCENT_POLICY;
            data.pvData = &accent;
            data.cbData = sizeof(accent);
            setWindowCompositionAttribute(hWnd, &data);
        }
    }
}
void ed_bgShower::paintEvent(QPaintEvent * ev){
    auto tem = updateMask();
    setMask(tem);
}

QRegion ed_bgShower::updateMask(){
    QRegion tem = pmw->edlayout->region;
    if(pMovingUnit){
        auto pos = pMovingUnit->mapToGlobal(QPoint(0,0));
        auto geo = pMovingUnit->geometry();
         tem = tem.united(QRect(pos.x(),pos.y(),geo.width(),geo.height()));
    }
    return tem;
}
