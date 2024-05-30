#include "mainwindow.h"
#include "ed_block.h"
#include "qpainter.h"
#include "ui_mainwindow.h"
#include "SysFunctions.h"
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>
#include <cmath>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ui->groupBox->setStyleSheet("QGroupBox {border: 0;}");

    // // 设置边框颜色和宽度为0，相当于隐藏边框：
    // ui->groupBox->setStyleSheet("QGroupBox {border: 0px solid transparent;}");

    QList<FileInfo> icons = scanalldesktopfiles();

    for(int i=0;i<icons.size();i++){
        qDebug()<<icons[i].filePath;
        cd[i] = new ED_BLOCK(this,icons[i].icon.pixmap(256).toImage(),icons[i].name,icons[i].filePath);
        connect(cd[i], &ED_BLOCK::sendSelf, this, &MainWindow::getObject);

        cd[i]->move(i % 8 * 115, i / 8 * 144);

        positionoccupied[i/8][i%8]=true;
        iconNum++;

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_test_pushButton_clicked()
{
    qDebug() << "clicked";
}
void MainWindow::getObject(ED_BLOCK *w)
{
    // 收到小部件的点击信号，移动初始化
    moving = true;
    temp = w;
    startP = cursor().pos() - this->pos();
    yuanP = temp->pos();
    /*将此小部件提升到父小部件堆栈的顶部*/
    temp->raise();
    int row=yuanP.y()/144;
    int col=yuanP.x()/115;
    if(row>=0&&row<10&&col>=0&&col<22)
    {
        positionoccupied[row][col]=false;
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // 小部件移动
    if (moving)
        if (temp)
            temp->move(yuanP.x() + event->x() - startP.x(), yuanP.y() + event->y() - startP.y());
}

// 拖拽对象置顶，卡牌积压的时候，拖动的那张卡牌置顶
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(moving){

        // qDebug("mw-releasse");
        int dtwidth = 2560;
        int dtheight = 1440;
        int mindeltaX = dtwidth;
        int mindeltaY = dtheight;
        int bpx, bpy;
        // 遍历各个点位寻找最小差异的位置
        /*for (int j = 0; j < 10; j++)
        {
            int deltaY = abs(temp->pos().y() - 144 * j);
            if (deltaY < mindeltaY)
            {
                mindeltaY = deltaY;
                bpy = 144 * j;
            }
        }
        for (int j = 0; j < 22; j++)
        {
            int deltaX = abs(temp->pos().x() - 115 * j);
            if (deltaX < mindeltaX)
            {
                mindeltaX = deltaX;
                bpx = 115 * j;
            }
        }*/
        for(int j=0;j<10;j++)
        {
            for(int k=0;k<22;k++)
            {
                int deltaY = abs(temp->pos().y() - 144 * j);
                int deltaX = abs(temp->pos().x() - 115 * k);
                if((deltaX+deltaY<mindeltaX+mindeltaY)&&(positionoccupied[j][k]==false))
                {
                    mindeltaX=deltaX;
                    mindeltaY=deltaY;
                    bpy=144*j;
                    bpx=115*k;
                }
            }
        }

        temp->move(bpx, bpy);
        positionoccupied[bpy/144][bpx/115]=true;
        temp->raise();
        moving = false;

    }

}
void MainWindow::customContextMenu(QPoint const&)
{
    // ContextMenu::show(QStringList() << "D:/", (void *)winId(), QCursor::pos());
}

void MainWindow::setIconScale(double scale){
    for(int i=0;i<iconNum;i++){
        if(cd[i]){
            cd[i]->gv->setScale(scale);
        }
    }
}

void MainWindow::setIconHight(int val){
    for(int i=0;i<iconNum;i++){
        if(cd[i]){
            cd[i]->vl->setSpacing(val);
        }
    }
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    setIconScale((double)value/50);
}


void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    setIconHight(value);
}

bool MainWindow::isPositionEmpty(const QPoint& position) const
{
    //在MainWindow类中使用这个数组来检查位置是否为空
    int row=position.y()/144;
    int col=position.x()/115;
    if(row>=0&&row<10&&col>=0&&col<22)
    {
        return !positionoccupied[row][col];
        //位置没有被占据时返回true；
    }
    return false;
    //位置超出窗口返回false；
}

void MainWindow::paintEvent(QPaintEvent * ev)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/images/background"),QRect());
}
