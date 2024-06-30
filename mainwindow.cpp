#include "mainwindow.h"
#include "ed_bgshower.h"
#include "ed_container.h"
#include "ed_block.h"
#include "ed_dock.h"
#include "ed_editbox.h"
#include "ed_hidetextblock.h"
#include "qgraphicseffect.h"
#include "qpainter.h"
#include "ui_mainwindow.h"
#include "SysFunctions.h"
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>
#include <QFileDialog>
#include<qtimer.h>
#include"QScreen"
#include"QThread"
ED_Unit* pMovingUnit = nullptr;


void MainWindow::setupActions(){
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


    QAction* act2  = new QAction("改变复杂度");
    this->addAction(act2);

    connect(act2, &QAction::triggered, this, [=]()
    {
        for(ED_Unit* content:*(edlayout->contents)){
            content->changeSimpleMode();
        }
    });

    QAction* act3  = new QAction("切换背景");
    this->addAction(act3);
    connect(act3, &QAction::triggered, this, [=]()
    {
        setTransparent(!enable_background_transparent);
    });


    QAction* act4  = new QAction("退出程序");
    this->addAction(act4);
    connect(act4, &QAction::triggered, this, [=]()
            {
                QCoreApplication::quit() ;
            });

    /*QAction* act5  = new QAction("获取背景");
    this->addAction(act5);
    connect(act5, &QAction::triggered, this, [=]()
    {
        setVisible(false);
        QThread::msleep(200);
        QScreen *screen = QGuiApplication::primaryScreen();
        bgshower->captrued = screen->grabWindow(0);
        bgshower->show = true;
        bgshower->setVisible(true);
        setVisible(true);
    })*/;

    QAction* act6 =new QAction("新建小型格子");
    this->addAction(act6);
    connect(act6,&QAction::triggered, this, [=]()
    {
        auto bc = new ED_Container(this,2,2,2,15,15);
        InitAUnit(bc);
    });
    QAction* act7 =new QAction("新建中型格子");
    this->addAction(act7);
    connect(act7,&QAction::triggered, this, [=]()
            {
                auto bc = new ED_Container(this,3,3,3,20,20);
                InitAUnit(bc);
            });

    QAction* act8 =new QAction("新建大型格子");
    this->addAction(act8);
    connect(act8,&QAction::triggered, this, [=]()
            {
                auto bc = new ED_Container(this,4,4,4,30,30);
                InitAUnit(bc);
            });



    QAction* act9  = new QAction("新建dock栏");
    this->addAction(act9);
    connect(act9, &QAction::triggered, this, [=]()
            {
                auto dock = new ED_Dock(this,6,1,4);
                InitAUnit(dock);
            });

    /*QAction* act6  = new QAction("insert bg");
    this->addAction(act6);
    connect(act6, &QAction::triggered, this, [=]()
            {
                // inplace2(bgshower);

            });


    QAction* act7  = new QAction("lowerbg");
    this->addAction(act7);
    connect(act7, &QAction::triggered, this, [=]()
            {
                qDebug()<<"main windowr Pos:"<<pos()<<" geometry :"<<geometry()<<"rect: "<<rect();
                // bgshower->lower();
            });

    QAction* act8  = new QAction("blur");
    this->addAction(act8);
    connect(act8, &QAction::triggered, this, [=]()
    {

        // bgshower->setwinblur();
        // edlayout->setwinblur();
    });*/


}
void MainWindow::setupUnits(){
    // setMouseTracking(true);
    //设置背景
    setBlur(enable_background_blur);

    edlayout = new ED_Layout(this,20,12,5,10,10);
    edlayout->isMain = true;
    // qDebug()<<edlayout->W_Container()<<edlayout->H_Container();

    //获取图标
    QList<FileInfo> iconns = scanalldesktopfiles();
    QList<QString> nametem;
    for(int i=0;i<iconns.size();i++){
        qDebug()<<iconns[i].name<<iconns[i].type;
        int sizex=1;
        int sizey=1;

        ED_Unit* tem = nullptr;
        if(!nametem.contains(iconns[i].name))
            switch (iconns[i].type) {
            case FileInfo::HORI:
                tem = new ED_HideTextBlock(this,iconns[i].icon.pixmap(512),iconns[i].name,iconns[i].filePath,1,2);
                break;
            case FileInfo::VERT:
                tem = new ED_HideTextBlock(this,iconns[i].icon.pixmap(512),iconns[i].name,iconns[i].filePath,2,1);
                break;
            default:
                tem = new ED_BLOCK(this,iconns[i].icon.pixmap(256),iconns[i].name,iconns[i].filePath,sizex,sizey);
                break;
            }
        nametem.append(iconns[i].name);

        if(tem)
        {
            InitAUnit(tem);
            tem->raise();
        }
    }


    auto eb = new ED_EditBox(this);
    InitAUnit(eb);

    weatherwidget = new Weather(this,4,2);
    InitAUnit(weatherwidget);
    htkt = new Hitokoto(this,2,1);
    InitAUnit(htkt);


    //初始化一些
    pmw = this;
    bg = QPixmap(":/images/background");

    setVisible(true);
    edlayout->Update_Region();
    update();
    // bgshower->update();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),weatherwidget(nullptr)
{
    ui->setupUi(this);

    Init(this);

    setupUnits();

    setupActions();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePer01second())); // slotCountMessage是我们需要执行的响应函数
    timer->start(100); // 每隔0.1s

}


void MainWindow::InitAUnit(ED_Unit* aim){
    // connect(aim, &ED_Unit::sendSelf, this, &MainWindow::getObject);
    edlayout->InitAUnit(aim);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setScale(double scale){
    for(ED_Unit* content:*(edlayout->contents)){
        content->setScale(scale);
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

void MainWindow::updatePer01second(){
    // repaint();
}

void MainWindow::paintEvent(QPaintEvent * ev)
{
    if(!enable_background_transparent){
        QPainter painter(this);
        painter.drawPixmap(rect(),bg);
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent* ev) {
    edlayout->setVisible(!edlayout->Visible());
}

void MainWindow::onSelectBackground() {
    QString fileName = QFileDialog::getOpenFileName(this, "选择背景文件", "", "Images (*.png *.jpg *.bmp);;Videos (*.mp4 *.avi *.mkv)");
    qDebug() << "Selected file:" << fileName; // 调试输出文件路径
    if (!fileName.isEmpty()) {
        if (fileName.endsWith(".png") || fileName.endsWith(".jpg") || fileName.endsWith(".bmp")) {
            QPalette palette;
            QPixmap pixmap(fileName);
            if (pixmap.isNull()) {
                qDebug() << "Failed to load image";
            } else {
                bg = pixmap;
                repaint();
                qDebug() << "Image set as background";
            }
        }
    }
}

void  MainWindow::setTransparent(bool val){
    enable_background_transparent = val;
    if(enable_background_blur){
        bgshower->show = !val;
        bgshower->setVisible(!val);
        bgshower->captrued = bg;
    }
    // qDebug()<<transparent<<val;
}


void  MainWindow::setBlur(bool val){
    enable_background_blur = val;
    if(bgshower){
        bgshower->setEnabled(val);
        bgshower->setVisible(val);
    }
    else{
        if(val){
            bgshower = new ED_BGShower(this);
            bgshower->setFixedSize(size());
            bgshower->setVisible(enable_background_blur);
            bgshower->move(0,0);
            bgshower->setVisible(true);
        }
    }

    // qDebug()<<transparent<<val;
}
