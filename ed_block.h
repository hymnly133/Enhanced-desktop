#ifndef ED_BLOCK_H
#define ED_BLOCK_H

#include "qboxlayout.h"
#include "qgraphicsview.h"
#include "qlabel.h"
#include <QWidget>

class ED_BLOCK : public QWidget
{
    Q_OBJECT;
    QVBoxLayout* vl;
    QGraphicsView* gv ;
    QLabel* lb ;
public:
    explicit ED_BLOCK(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void sendSelf(ED_BLOCK *self);
public slots:
    // void getformGV();
};


#endif // ED_BLOCK_H
