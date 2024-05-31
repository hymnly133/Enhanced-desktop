#include "ed_layout.h"
#include<cmath>

ED_Layout::ED_Layout( QWidget *father,int row, int col,int space) {
    this->row = row;
    this->col = col;
    this->space = space;
    W_Father = father->width();
    H_Father = father->height();
    W_Block = W_Father/row;
    H_Block = H_Father/col;
    for(int i=0;i<row;i++){
        for(int k=0;k<col;k++){
            blocks[i][k] = new little_Block();
            blocks[i][k]->indX = i;
            blocks[i][k]->indY = i;
            blocks[i][k]->w = W_Block;
            blocks[i][k]->h = H_Block;
            blocks[i][k]->posX = i*W_Block;
            blocks[i][k]->posY = k*H_Block;
            blocks[i][k]->occupied = false;
        }
    }
}


QPoint ED_Layout::NearestBlockInd(QPoint point){
    return QPoint(point.x()/W_Block,point.y()/H_Block);

}
QPoint ED_Layout::NearestBlockInd(int posx,int posy){
return QPoint(posx/W_Block,posy/H_Block);
}

//从Block序号获取中心坐标
QPoint ED_Layout::BlockInd2CenterPoint(QPoint ind){
    return blocks[ind.x()][ind.y()]->CenterPoint();
}
QPoint ED_Layout::BlockInd2CenterPoint(int x,int y){
    return blocks[x][y]->CenterPoint();
}

//从Block序号获取是否占用
bool& ED_Layout::Occupied(QPoint ind){
    return blocks[ind.x()][ind.y()]->occupied;
}
bool& ED_Layout::Occupied(int x,int y){
    return blocks[x][y]->occupied;
}

bool ED_Layout::OKForUnit(ED_Unit* aim,int xind,int yind){
    int x = aim->sizeX;
    int y = aim->sizeY;
    if(x+xind>row)return false;
    if(y+yind>col) return false;
    for(int i=0;i<x;i++){
        for(int k=0;k<y;k++){
            if(Occupied(xind+i,yind+k)) return false;
        }
    }
    return true;
}

//将一个ED_Unit放置在Block中，并在双方的变量中纪律以便之后识别
void ED_Layout::put_ED_Unit(ED_Unit* aim,QPoint ind){
    return put_ED_Unit(aim,ind.x(),ind.y());
}

void ED_Layout::put_ED_Unit(ED_Unit* aim,int xind,int yind){
    int x = aim->sizeX;
    int y = aim->sizeY;
    for(int i=0;i<x;i++){
        for(int k=0;k<y;k++){
            Occupied(xind+i,yind+k) = true;
            blocks[xind+i][yind+k]->content = aim;
        }
    }
    aim->LayoutBlockX = xind;
    aim->LayoutBlockY = yind;
    int w= aim->sizeX*W_Block-2*space;
    int h= aim->sizeY*H_Block-2*space;
    aim->setFixedSize(w,h);
    aim->move(xind*W_Block+space,yind*H_Block+space);
    aim->raise();
}


void ED_Layout::RemoveAUnit(ED_Unit* aim){
    int x = aim->sizeX;
    int y = aim->sizeY;
    int xind = aim->LayoutBlockX;
    int yind = aim->LayoutBlockY ;
    for(int i=0;i<x;i++){
        for(int k=0;k<y;k++){
            Occupied(xind+i,yind+k) = false;
            blocks[xind+i][yind+k]->content = NULL;
        }
    }
    aim->LayoutBlockX = -1;
    aim->LayoutBlockY = -1;
}
//根据一个Block索引获取对应的ED_Unit指针
ED_Unit* ED_Layout::getUnitFromBlock(int xind,int yind)
{
    if(Occupied(xind,yind))
    {
        return blocks[xind][yind]->content;
    }
    else
    {
        return nullptr;
    }
    //若无返回空指针
}
ED_Unit* ED_Layout::getUnitFromBlock(QPoint ind)
{
    return getUnitFromBlock(ind.x(),ind.y());
}
//将一个ED_Unit按序号最下且可放置的位置放置
void ED_Layout::add_ED_Unit(ED_Unit* aim)
{
    for(int j=0;j<col;j++)
    {
        for(int i=0;i<row;i++)
        {
            if(OKForUnit(aim,i,j))
            {
                put_ED_Unit(aim,i,j);
                return;
            }
        }
    }
}

QPoint ED_Layout::NearestEmptyBlockInd(ED_Unit* aim,int posx,int posy)
{
    int mindeltaw=W_Father;
    int mindeltah=H_Father;
    int bpw,bph;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            int deltaw=abs(posx-i*W_Block);
            int deltah=abs(posy-j*H_Block);
            if((deltaw+deltah<mindeltaw+mindeltah)&&(OKForUnit(aim,i,j)))
            {
                mindeltaw=deltaw;
                mindeltah=deltah;
                bpw=i;
                bph=j;
            }
        }
    }
    return QPoint(bpw,bph);
}
