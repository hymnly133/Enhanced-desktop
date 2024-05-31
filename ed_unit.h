#ifndef ED_UNIT_H
#define ED_UNIT_H

#include <QWidget>
class ED_Layout;
class ED_Unit : public QWidget
{
    Q_OBJECT
public:
    enum ED_TYPE {Unit,Block,Container,H_Block};
    ED_TYPE type = Unit;
    ED_Layout* edlayout;
    int sizeX;
    int sizeY;
    int ind;
    int LayoutBlockX = -1;
    int LayoutBlockY = -1;
    explicit ED_Unit(QWidget *parent,int sizex,int sizey);
    virtual void update_after_resize();
    void removeFromLayout();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    virtual void double_click_action();
    virtual void single_click_action();

    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
signals:
    void sendSelf(ED_Unit *self);
public slots:
    void getaClick();
    void getaDoubleClick();
};


#endif // ED_UNIT_H
