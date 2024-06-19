#ifndef ED_UNIT_H
#define ED_UNIT_H

#include <QWidget>
class ED_Layout;
class ED_Unit : public QWidget
{
    Q_OBJECT
public:
    enum ED_TYPE {Unit,Block,Container};
    ED_TYPE type = Unit;
    ED_Layout* edlayout;
    bool moving;
    QPoint relativeP;
    int sizeX;
    int sizeY;
    int ind;
    int LayoutBlockX = -1;
    int LayoutBlockY = -1;
    explicit ED_Unit(QWidget *parent,int sizex,int sizey);
    virtual void update_after_resize();
    void removeFromLayout();


public:
    virtual void double_click_action();
    virtual void single_click_action();
    virtual void mouse_move_action();
    virtual void mouse_release_action();



    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
public slots:
    void getaClick();
    void getaDoubleClick();
};


#endif // ED_UNIT_H
