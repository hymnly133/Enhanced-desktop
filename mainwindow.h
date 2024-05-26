#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_test_pushButton_clicked();

private:
    Ui::MainWindow *ui;

protected:
    void mouseMoveEvent(QMouseEvent *event);  //鼠标移动
    void mousePressEvent(QMouseEvent *ev);    //鼠标单击
private:
    QPoint m_pt;         //m_pt=差值=鼠标当前位置-窗口左上角点
};
#endif // MAINWINDOW_H
