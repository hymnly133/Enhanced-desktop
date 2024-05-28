#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
    MouseHook mh;
    // virtual void mousePressEvent(QMouseEvent *event);
    // virtual void mouseReleaseEvent(QMouseEvent *event);
    // virtual void mouseDoubleClickEvent(QMouseEvent *event);
    // virtual void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_test_pushButton_clicked();

private:
    Ui::MainWindow *ui;
     //m_pt=差值=鼠标当前位置-窗口左上角点

};

#endif // MAINWINDOW_H
