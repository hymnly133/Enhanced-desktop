#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ed_block.h"
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
    // virtual void mousePressEvent(QMouseEvent *event);
    // virtual void mouseReleaseEvent(QMouseEvent *event);
    // virtual void mouseDoubleClickEvent(QMouseEvent *event);
    // virtual void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_test_pushButton_clicked();
    void getObject(ED_BLOCK *w);
    void customContextMenu(QPoint const& point);
    void setIconScale(double Scale);
    void on_verticalSlider_valueChanged(int value);
    void setIconHight(int val);
    void on_verticalSlider_2_valueChanged(int value);
    bool isPositionEmpty(const QPoint& position) const;

private:
    Ui::MainWindow *ui;
    ED_BLOCK* cd[200];
    int iconNum = 0;
    ED_BLOCK *temp;
    QPoint startP;
    QPoint yuanP;
    bool moving = false;
    bool positionoccupied[10][22]={};
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent * ev) override;

};

#endif // MAINWINDOW_H
