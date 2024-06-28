#include "mainwindow.h"
#include "block_container.h"
#include "ed_block.h"
#include "qpainter.h"
#include "ui_mainwindow.h"
#include "SysFunctions.h"
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Init(this);

    edlayout = new ED_Layout(this,20,15,5);


    QList<FileInfo> iconns = scanalldesktopfiles();

    auto bc = new Block_Container(this,4,4);
    InitAUnit(bc);
    bc->InitLayout(3,3,3);

    auto bc_ = new Block_Container(this,3,3);
    InitAUnit(bc_);
    bc_->InitLayout(5,5,3);

    for(int i=0;i<iconns.size();i++){
        qDebug()<<iconns[i].filePath;
        int sizex=1;
        int sizey=1;
        if(i%2==0){
            sizex = 2;
        }
        if(i%3==0){
            sizey=2;
        }
        auto tem = new ED_BLOCK(this,iconns[i].icon.pixmap(256).toImage(),iconns[i].name,iconns[i].filePath,sizex,sizey);

        if(i <=2){
            bc->edlayout->InitAUnit(tem);
        }
        else{
            InitAUnit(tem);
        }


        tem->raise();
    }
    pmw = this;

    // mainwindow.cpp


    // 只要将某个QAction添加给对应的窗口, 这个action就是这个窗口右键菜单中的一个菜单项了
    // 在窗口中点击鼠标右键, 就可以显示这个菜单
    setContextMenuPolicy(Qt::ActionsContextMenu);
    // 给当前窗口添加QAction对象
    QAction* act1  = new QAction("改变可见");
    QAction* act2 = new QAction("Java");
    QAction* act3  = new QAction("Python");
    this->addAction(act1);
    this->addAction(act2);
    this->addAction(act3);
    connect(act1, &QAction::triggered, this, [=]()
    {
        edlayout->setVisible(!edlayout->Visible());
    });

}
void MainWindow::InitAUnit(ED_Unit* aim){
    // connect(aim, &ED_Unit::sendSelf, this, &MainWindow::getObject);
    edlayout->InitAUnit(aim);
    aim->ind = iconNum;
    iconNum++;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setIconScale(double scale){
    for(ED_Unit* content:*(edlayout->contents)){
        if(content->type == ED_Unit::Block){
            ED_BLOCK* p = (ED_BLOCK*)content;
            p->gv->setScale(scale);
        }
    }
}

void MainWindow::setIconHight(int val){
    for(ED_Unit* content:*(edlayout->contents)){
        if(content->type == ED_Unit::Block){
            ED_BLOCK* p = (ED_BLOCK*)content;
             p->vl->setSpacing(val);
        }
    }
}



void MainWindow::paintEvent(QPaintEvent * ev)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/images/background"),QRect());
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    setIconHight(value);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    setIconScale((double)value/50);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent* ev) {
    edlayout->setVisible(!edlayout->Visible());
}
