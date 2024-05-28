#ifndef SYSFUNCTIONS_H
#define SYSFUNCTIONS_H
#include<windows.h>
#include"mainwindow.h"
#include"mousehook.h"
void Init(MainWindow* mainwindow);
void inplace(MainWindow* mainwindow);
void InitMouseHook(MouseHook* mh);
#endif // SYSFUNCTIONS_H
