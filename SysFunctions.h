#ifndef SYSFUNCTIONS_H
#define SYSFUNCTIONS_H
#include<windows.h>
#include"mainwindow.h"
void Init(MainWindow* mainwindow);
void inplace();
void InitMouseHook();
QString Unicode2GBK(QString c);
QString Unicode2Utf(QString c);
QString GetCorrectUnicode(const QByteArray &ba);
#endif // SYSFUNCTIONS_H
