#include "mainwindow.h"
#include "ed_container.h"
#include "ed_block.h"
#include "ed_dock.h"
#include "qgraphicseffect.h"
#include "qpainter.h"
#include "ui_mainwindow.h"
#include "SysFunctions.h"
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>
QPixmap* pbg = nullptr;
ED_Unit* pMovingUnit = nullptr;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),weatherwidget(nullptr)
{
    ui->setupUi(this);

    Init(this);

    //设置背景
    bgshower = new ed_bgShower(this);
    bgshower->setFixedSize(size());
    bgshower->setVisible(true);
    bgshower->lower();


    edlayout = new ED_Layout(this,20,15,5,10,10);
    // qDebug()<<edlayout->W_Container()<<edlayout->H_Container();

    //获取图标
    QList<FileInfo> iconns = scanalldesktopfiles();

    auto bc = new ED_Container(this,4,4,3,3,5);
    InitAUnit(bc);
    // bc->InitLayout();

    auto dock = new ED_Dock(this,6,2,4);
    InitAUnit(dock);
    // dock->InitLayout();

    weatherwidget = new WEATHERWIDGET(this,2,1);
    InitAUnit(weatherwidget);

    auto bc_ = new ED_Container(this,3,3,2,2,4);
    InitAUnit(bc_);
    // bc_->InitLayout();

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

    //初始化一些
    pmw = this;
    pbg = new QPixmap(":/images/background");



    // 只要将某个QAction添加给对应的窗口, 这个action就是这个窗口右键菜单中的一个菜单项了
    // 在窗口中点击鼠标右键, 就可以显示这个菜单
    setContextMenuPolicy(Qt::ActionsContextMenu);
    // 给当前窗口添加QAction对象
    QAction* act1  = new QAction("改变可见");
    this->addAction(act1);
    connect(act1, &QAction::triggered, this, [=]()
    {
        edlayout->setVisible(!edlayout->Visible());
    });
    setVisible(true);
    edlayout->Update_Region();
    update();
    bgshower->update();

    QAction* act2  = new QAction("Update_Region");
    this->addAction(act2);
    connect(act2, &QAction::triggered, this, [=]()
    {
        edlayout->Update_Region();
    });
    QAction* act3  = new QAction("update");
    this->addAction(act3);
    connect(act3, &QAction::triggered, this, [=]()
    {
        repaint();
        bgshower->update();
        int count=0;
        for(ED_Unit* content:*(edlayout->contents)){
            if(content->type == ED_Unit::Block){
                ED_BLOCK* p = (ED_BLOCK*)content;
                qDebug()<<++count<<" "<<p->name;

            }
        }
    });
    QAction* act4  = new QAction("updateMask");
    this->addAction(act4);
    connect(act4, &QAction::triggered, this, [=]()
    {
        bgshower->updateMask();
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
    painter.drawPixmap(rect(),*pbg);
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
