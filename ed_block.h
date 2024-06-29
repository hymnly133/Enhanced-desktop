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

    QColor mainColor;
    QPixmap iconmap;
    static int default_size;
public:
    QString name;
    PictureBox* gv ;
    QVBoxLayout* vl;
    explicit ED_BLOCK(QWidget *parent,QImage image,QString _name,QString _cmd,int sizex =1,int sizey=1);
    void update_after_resize() override;
    void mouse_enter_action() override;
    void mouse_leave_action()override;
protected:
    void double_click_action() override;
    void paintEvent(QPaintEvent *event) override;

};


#endif // ED_BLOCK_H
