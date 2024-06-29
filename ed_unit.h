#ifndef ED_UNIT_H
#define ED_UNIT_H
#include "style.h"
#include <QWidget>
#include<qlabel.h>
class ED_Layout;

class ED_Unit : public QWidget
{
    Q_OBJECT
public:
    enum ED_TYPE {Unit,Block,Container,FixedContainer};
    ED_TYPE type = Unit;
    ED_Layout* edlayout;
    bool moving;
    bool showRect = true;
    bool showLight = true;
    bool showSide = true;
    QPoint relativeP;
    int sizeX;
    int sizeY;
    int ind;
    int aim_Alpha =  sleep_alpha;
    bool alwaysShow = false;
    bool simpleMode = false;
    int LayoutBlockX = -1;
    int LayoutBlockY = -1;
    explicit ED_Unit(QWidget *parent,int sizex,int sizey);

    void removeFromLayout();

    virtual void update_after_resize();
    virtual void double_click_action();
    virtual void single_click_action();
    virtual void mouse_move_action();
    virtual void mouse_release_action();
    virtual void mouse_enter_action();
    virtual void mouse_leave_action();
    virtual void setBlockSize(int w,int h);
    virtual void changeToSimpleMode();
    virtual void changeToComplexMode();

    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *) override;                      //进入QWidget瞬间事件
    void leaveEvent(QEvent *) override;                      //离开QWidget瞬间事件
    void paintEvent(QPaintEvent *event) override;
    void setwinblur();
    void setSimpleMode(bool);
    void changeSimpleMode();

public slots:
    void getaClick();
    void getaDoubleClick();
};


#endif // ED_UNIT_H
