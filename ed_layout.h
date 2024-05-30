#ifndef ED_LAYOUT_H
#define ED_LAYOUT_H

#include "ed_unit.h"
#include "qwidget.h"
class ED_Layout
{
    struct little_Block{
        int indX;
        int indY;
        int posX;
        int posY;
        int w;
        int h;
        bool occupied;
        ED_Unit* content;
        int CenterX(){
            return posX +w/2;
        }
        int CenterY(){
            return posY +h/2;
        }
        QPoint CenterPoint(){
            return QPoint(CenterX(),CenterY());
        }
    };
    int row;
    int col;
    int W_Father;
    int H_Father;
    int W_Block;
    int H_Block;
    little_Block blocks[30][30];
public:
    ED_Layout(int row, int col, QWidget *father);
    // QPoint NearestBlockInd(QPoint point);
    // QPoint NearestBlockInd(int x,int y);

    // QPoint BlockInd2CenterPoint(QPoint ind);
    // QPoint BlockInd2CenterPoint(int x,int y);

    // bool Occupied(QPoint ind);
    // bool Occupied(int x,int y);

    // void put_ED_Unit(ED_Unit* aim,int xind,int yind);
    // QPoint searchIndOfUnit(ED_Unit* aim);
    // ED_Unit* getUnitFromBlock(int xind,int yind);
};

#endif // ED_LAYOUT_H
