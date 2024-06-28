#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ed_layout.h"
#include <QMainWindow>
#include <mousehook.h>

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
    ED_Layout* edlayout;
    ED_Unit* cds[200];

private slots:;
    void setIconScale(double Scale);
    void setIconHight(int val);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    int iconNum = 0;
    ED_Unit *temp;
    QPoint startP;
    QPoint fromP;
    QPoint relativeP;
    QPoint yuanP;
    bool moving = false;
    void InitAUnit(ED_Unit* aim);
protected:
    void paintEvent(QPaintEvent * ev) override;
    void mouseDoubleClickEvent(QMouseEvent* ev) override;

};
extern MainWindow* pmw;
#endif // MAINWINDOW_H
