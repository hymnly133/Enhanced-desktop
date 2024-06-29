#ifndef ED_HIDETEXTBLOCK_H
#define ED_HIDETEXTBLOCK_H

#include "ed_unit.h"
#include "picturebox.h"
#include "qlabel.h"
class ED_HideTextBlock:public ED_Unit
{
public:

    QLabel* lb ;
    QString cmd;
    QString name;
    static int default_size;
public:
    PictureBox* gv ;
    explicit     ED_HideTextBlock(QWidget *parent,QPixmap image,QString name,QString cmd,int sizex,int sizey);

    void update_after_resize() override;
protected:
    void double_click_action() override;
    void single_click_action() override;

    void paintEvent(QPaintEvent *event) override;
public slots:
    void getaClick();
    void getaDoubleClick();
};

#endif // ED_HIDETEXTBLOCK_H
