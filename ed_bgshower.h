#ifndef ED_BGSHOWER_H
#define ED_BGSHOWER_H

#include <QWidget>

class ed_bgShower : public QWidget
{
    Q_OBJECT
public:
    explicit ed_bgShower(QWidget *parent = nullptr);
    QRegion updateMask();
public:
    void paintEvent(QPaintEvent * ev) override;
signals:
};

#endif // ED_BGSHOWER_H
