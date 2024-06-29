#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dsvideoplayer.h"
#include "ed_bgshower.h"
#include "ed_layout.h"
#include <QMainWindow>
#include <mousehook.h>
#include <QPushButton>  // 添加QPushButton头文件
#include "weatherwidget.h"
#include "hitokoto.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    ed_bgShower* bgshower;
    bool transparent =true;
    bool moving = false;

    ED_Layout* edlayout;
    QPixmap bg;
    WEATHERWIDGET *weatherwidget;
    Hitokoto *htkt;

    void InitAUnit(ED_Unit* aim);
    void paintEvent(QPaintEvent * ev) override;
    void mouseDoubleClickEvent(QMouseEvent* ev) override;
    QPushButton *selectBackgroundButton;  // 新增：选择背景按钮
    // DSVideoPlayer *videoPlayer;  // 新增：用于视频播放

private:
    void setupActions();
    void setupUnits();
    void setTransparent(bool val);

private slots:;
    void setIconScale(double Scale);
    void setIconHight(int val);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_valueChanged(int value);
    void onSelectBackground();  // 新增：选择背景文件槽函数
    void updatePer01second();


};
extern MainWindow* pmw;
extern ED_Unit* pMovingUnit;

#endif // MAINWINDOW_H
