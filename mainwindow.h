#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "card.h"
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

private:
    Ui::MainWindow *ui;
    ED_BLOCK* cd[8];
    ED_BLOCK *temp;
    QPoint startP;
    QPoint yuanP;
    bool moving;
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

};

#endif // MAINWINDOW_H
