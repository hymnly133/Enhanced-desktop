#ifndef ED_BLOCK_H
#define ED_BLOCK_H

#include "ed_unit.h"
#include "picturebox.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include <QWidget>

class ED_BLOCK : public ED_Unit
{
    Q_OBJECT;

    QLabel* lb ;
    QString cmd;
    QString name;
    int size = 200;
public:
        PictureBox* gv ;
        QVBoxLayout* vl;
    explicit ED_BLOCK(QWidget *parent,QImage image,QString name,QString cmd);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void double_click_action();
    void single_click_action();
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
public slots:
    void getaClick();
    void getaDoubleClick();
};


#endif // ED_BLOCK_H
