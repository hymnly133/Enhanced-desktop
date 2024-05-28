#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>

class card:public QWidget
{
    Q_OBJECT
public:
    explicit card(QWidget *parent = nullptr);
    ~card();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void sendSelf(card *w);
};

#endif // CARD_H
