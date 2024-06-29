#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QWidget>
#include <QImage>
#include <QPixmap>


class PictureBox : public QWidget
{
    Q_OBJECT
public:
    enum PB_MODE {FIXED_SIZE, FIX_SIZE_CENTRED, AUTO_ZOOM, AUTO_SIZE};
    explicit PictureBox(QWidget *parent=0,double m_scale =1.0);
    void setMode(PB_MODE mode);
    void setScale(double scale);
    ~PictureBox();
private:
    QPixmap m_pixmap;
    double m_scale;
    PB_MODE m_mode;
    QBrush m_brush;
protected:
    void paintEvent(QPaintEvent * event);

public slots:
    bool setImage(QPixmap &image, double scale =1.0,double pixresize =1.0);
    void setBackground(QBrush brush);
};
#endif
