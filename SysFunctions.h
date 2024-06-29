#ifndef SYSFUNCTIONS_H
#define SYSFUNCTIONS_H
#include<windows.h>
#include <QIcon>
#include"mainwindow.h"
void Init(MainWindow* mainwindow);
void inplace();
void InitMouseHook();
QString Unicode2GBK(QString c);
QString Unicode2Utf(QString c);
QString GetCorrectUnicode(const QByteArray &ba);
QString elidedLineText(QWidget *pWidget, int nLine, QString strText);
extern bool ShowRect;
extern bool ShowSide;
struct FileInfo
{
    //定义返回的结构体
    QString name;
    QString filePath;
    QIcon icon;
};
QList<FileInfo> scanalldesktopfiles();
void paintRect(QWidget* aim,QColor color);
void repaintAround(QWidget* aim);
QColor pixmapMainColor(QPixmap p, double bright);
void paintside(QWidget* aim,QColor color);
#endif // SYSFUNCTIONS_H
