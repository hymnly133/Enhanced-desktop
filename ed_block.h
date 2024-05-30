#ifndef ED_BLOCK_H
#define ED_BLOCK_H

#include "picturebox.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include <QWidget>

class ED_BLOCK : public QWidget
{
    Q_OBJECT;
    QVBoxLayout* vl;

    QLabel* lb ;
    QString cmd;
    QString name;
    int size = 150;
public:
        PictureBox* gv ;
    explicit ED_BLOCK(QWidget *parent,QImage image,QString name,QString cmd);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void double_click_action();
    void single_click_action();
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
signals:
    void sendSelf(ED_BLOCK *self);
public slots:
    void getaClick();
    void getaDoubleClick();
};


#endif // ED_BLOCK_H
