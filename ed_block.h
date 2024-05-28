#ifndef ED_BLOCK_H
#define ED_BLOCK_H

#include "picturebox.h"
#include "qboxlayout.h"
#include "qgraphicsview.h"
#include "qlabel.h"
#include <QWidget>

class ED_BLOCK : public QWidget
{
    Q_OBJECT;
    QVBoxLayout* vl;
    PictureBox* gv ;
    QLabel* lb ;
public:
    explicit ED_BLOCK(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void double_click_action();
    void single_click_action();
    void mouseDoubleClickEvent(QMouseEvent *event) override;
signals:
    void sendSelf(ED_BLOCK *self);
public slots:
    void getaClick();
    void getaDoubleClick();
};


#endif // ED_BLOCK_H
