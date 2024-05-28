#ifndef ED_BLOCK_H
#define ED_BLOCK_H

#include <QWidget>

class ED_BLOCK : public QWidget
{
    Q_OBJECT
public:
    explicit ED_BLOCK(QWidget *parent = nullptr);
//     ~ED_BLOCK();
// protected:
//     void paintEvent(QPaintEvent *event) override;
//     void mousePressEvent(QMouseEvent *event) override;
// signals:
//     void sendSelf(ED_BLOCK *self);
};


#endif // ED_BLOCK_H
