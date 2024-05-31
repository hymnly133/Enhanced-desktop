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
public:
    int row;
    int col;
    int W_Father;
    int H_Father;
    int W_Block;
    int H_Block;
    int space;
    QWidget* father;
    QVector<ED_Unit*>* contents = new QVector<ED_Unit*>;
    little_Block* blocks[30][30];
public:
    ED_Layout(QWidget *father,int row, int col,int space);
/*
 *
 *
 *
 *     ED_Unit中有如下参数，以便调用和识别在布局中的位置和大小
 *     int sizeX;//横向Block大小
 *    int sizeY;//竖向Block大小
        int LayoutBlockX;//Block XY索引
        int LayoutBlockY;
*/
    // 从坐标获得最近的Block序号
    QPoint NearestBlockInd(QPoint point);
    QPoint NearestBlockInd(int posx,int posy);

    //从Block序号获取中心坐标
    QPoint BlockInd2CenterPoint(QPoint ind);
    QPoint BlockInd2CenterPoint(int x,int y);

    //从Block序号获取是否占用
    bool& Occupied(QPoint ind);
    bool& Occupied(int x,int y);

    //将一个ED_Unit放置在Block中，并在双方的变量中纪律以便之后识别
    void put_ED_Unit(ED_Unit* aim,int xind,int yind);
    void put_ED_Unit(ED_Unit* aim,QPoint ind);

    // 从坐标获得最近的可放置Block序号
    QPoint NearestEmptyBlockInd(ED_Unit* aim,int posx,int posy);
    QPoint NearestEmptyBlockInd(ED_Unit* aim,QPoint pos);

    //将一个Unit从坐标体系中脱离
    void RemoveAUnit(ED_Unit* aim);
    //将一个Unit加入到坐标体系中
    void InplaceAUnit(ED_Unit* aim);
    void InitAUnit(ED_Unit* aim);

    //判断一个ED_Unit的左上角放置在该Block中是否合法
    bool OKForUnit(ED_Unit* aim,int xind,int yind);

    //根据一个Block索引获取对应的ED_Unit指针
    ED_Unit* getUnitFromBlock(int xind,int yind);
    ED_Unit* getUnitFromBlock(QPoint ind);

    //将一个ED_Unit按序号最下且可放置的位置放置
    void default_Put_ED_Unit(ED_Unit* aim);
};

#endif // ED_LAYOUT_H
