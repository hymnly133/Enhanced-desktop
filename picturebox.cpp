#include "picturebox.h"
#include "SysFunctions.h"
#include <QPainter>
#include <QDebug>
#include "style.h"
static const int IMAGE_WIDTH = 300;
static const int IMAGE_HEIGHT = 300;
static const QSize IMAGE_SIZE = QSize(IMAGE_WIDTH, IMAGE_HEIGHT);


PictureBox::PictureBox(QWidget *parent,double m_scale) : QWidget(parent)
{
    m_pixmap = QPixmap(IMAGE_SIZE);
    m_pixmap.fill();
    this->m_scale = m_scale;
    m_mode = FIXED_SIZE;
    m_brush = QBrush(Qt::white);
}

void PictureBox::setBackground(QBrush brush)
{
    m_brush = brush;
    update();
}

void PictureBox::setMode(PB_MODE mode)
{
    m_mode = mode;
    if(m_mode == AUTO_SIZE)
    {
        setFixedSize(m_pixmap.size() * m_scale);
    }
    else
    {

        setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
        setMinimumSize(0, 0);
    }
    update();
}

void PictureBox::setScale(double scale){
        m_scale = qBound(0.01, scale, 100.0);
    int image_width = m_pixmap.width();
    int image_height = m_pixmap.height();
    setFixedSize(image_width * m_scale, image_height *m_scale);
    update();
}

bool PictureBox::setImage(QPixmap &image, double scale,double pixresize)
{
    if(image.isNull())
    {
        return false;
    }
    m_pixmap = image;
    m_pixmap =m_pixmap.scaled(QSize(image.width() * pixresize, image.height() *pixresize)
                               , Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    setScale(scale);

    if(m_mode == AUTO_SIZE)
    {
        setFixedSize(m_pixmap.size() * m_scale);
    }
    update();
    return true;
}

void PictureBox::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBackground(m_brush);
    painter.eraseRect(rect());

    double window_width, window_height;
    double image_width, image_height;
    double r1, r2, r;
    int offset_x, offset_y;
    QPixmap m_logopix;
    switch (m_mode)
    {
    case FIXED_SIZE:
    case AUTO_SIZE:
        painter.scale(m_scale, m_scale);

        painter.drawPixmap(0, 0, m_pixmap);
        break;

    case FIX_SIZE_CENTRED:
        window_width = width();
        window_height = height();
        image_width = m_pixmap.width();
        image_height = m_pixmap.height();
        offset_x = (window_width - m_scale * image_width) / 2;
        offset_y = (window_height - m_scale * image_height) / 2;
        painter.translate(offset_x, offset_y);

        m_logopix = m_pixmap.scaled(QSize(image_width * m_scale, image_height *m_scale)
                                            , Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        // painter.scale(m_scale, m_scale);
        painter.drawPixmap(0, 0, m_logopix);


        // painter.scale(m_scale, m_scale);
        // painter.drawPixmap(0, 0, m_pixmap);
        break;

    case AUTO_ZOOM:

        window_width = width();
        window_height = height();
        image_width = m_pixmap.width();
        image_height = m_pixmap.height();
        r1 = window_width / image_width;
        r2 = window_height / image_height;
        if(enable_image_fill==true)
            r = qMax(r1, r2);
        else
            r=qMin(r1,r2);
        m_logopix = m_pixmap.scaled(QSize(image_width * r, image_height *r)
                                    , Qt::IgnoreAspectRatio, Qt::SmoothTransformation);


        image_width = m_logopix.width();
        image_height = m_logopix.height();
        int dis_x = (window_width-image_width)/2;
        int dis_y = (window_height-image_height)/2;

        // qDebug()<<window_width<<window_height<<image_width<<image_height<<r<<dis_x<<dis_y<<parentWidget()->size();

        painter.drawPixmap(dis_x, dis_y, m_logopix);
        break;
    }
    // QPainter p(this);
    // p.setPen(QColor("green")); //设置画笔记颜色
    // p.drawRect(0, 0, width() -1, height() -1); //绘制边框

    paintSide(this,QColor("red"));
}
PictureBox::~PictureBox()
{

}
