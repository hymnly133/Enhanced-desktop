#include "mainwindow.h"
#include "ed_container.h"
#include "ed_block.h"
#include "ed_dock.h"
#include "qgraphicseffect.h"
#include "ui_mainwindow.h"
#include "SysFunctions.h"
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>
#include <QFileDialog>
ED_Unit* pMovingUnit = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), weatherwidget(nullptr),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Init(this);

    //设置背景
    bgshower = new ed_bgShower();
    bgshower->setFixedSize(size()/2);
    bgshower->setVisible(true);
    bgshower->raise();
    bgshower->move(0,0);
    bgshower->setWindowTitle("BG_Shower");
    inplace2(bgshower);

    // 初始化选择背景按钮
    selectBackgroundButton = new QPushButton("选择背景", this);
    connect(selectBackgroundButton, &QPushButton::clicked, this, &MainWindow::onSelectBackground);

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
        auto tem = new ED_BLOCK(this,iconns[i].icon.pixmap(256),iconns[i].name,iconns[i].filePath,sizex,sizey);

        if(i <=2){
            bc->edlayout->InitAUnit(tem);
        }
        else{
            InitAUnit(tem);
        }

        tem->raise();
    }
    auto scene = new QGraphicsScene(this);
    scene->addPixmap(iconns[0].icon.pixmap(512));

    ui->graphicsView->setScene(scene);
    ui->pushButton->setIcon(iconns[0].icon);
    //初始化一些
    pmw = this;
    bg = QPixmap(":/images/background");



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
    QAction* act4  = new QAction("exit");
    this->addAction(act4);
    connect(act4, &QAction::triggered, this, [=]()
    {
         QCoreApplication::quit() ;

    });
    QAction* act5  = new QAction("print main window");
    this->addAction(act5);
    connect(act5, &QAction::triggered, this, [=]()
    {
        qDebug()<<"main windowr Pos:"<<pos()<<" geometry :"<<geometry()<<"rect: "<<rect();

    });
    QAction* act6  = new QAction("insert bg");
    this->addAction(act6);
    connect(act6, &QAction::triggered, this, [=]()
    {
        inplace(bgshower);
        // qDebug()<<"shower windowr Pos:"<<bgshower->pos()<<" geometry :"<<bgshower->geometry()<<"rect: "<<bgshower->rect();
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
    // QPainter painter(this);
    // painter.drawPixmap(rect(),bg);
    bgshower->repaint();
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
                // palette.setBrush(QPalette::Window, QBrush(pixmap));
                // this->setPalette(palette);
                qDebug() << "Image set as background";
            }

            // videoPlayer->stop();
            // videoPlayer->hide();
        } else {
            // if (videoPlayer->loadFile(fileName)) {
            //     videoPlayer->play();
            //     videoPlayer->show();
            //     qDebug() << "Video started";
            // } else {
            //     qDebug() << "Failed to load video";
            // }
        }
    }
}


