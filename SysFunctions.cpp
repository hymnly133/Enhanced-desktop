#include<windows.h>
#include"mainwindow.h"
#include"mousehook.h"
#include <QJsonObject>
MainWindow* pmw;

void mouse_move(int x,int y){
    qDebug()<<"move"<<x<<y;
    pmw->move(x,y);
}
void mouse_on(int x,int y){
    qDebug()<<"on"<<x<<y;
}
void mouse_off(int x,int y){
    qDebug()<<"off"<<x<<y;
}

void Init(MainWindow* mainwindow){


    // mainwindow->setWindowState(Qt::WindowFullScreen);
        qDebug()<<"Initing";
    mainwindow->setWindowFlags(Qt::FramelessWindowHint);
    mainwindow->mh.SetMouseMoveCallBack(mouse_move);
    mainwindow->mh.SetMouseOffCallBack(mouse_off);
    mainwindow->mh.SetMouseOnCallBack(mouse_on);
    qDebug()<<"Initing done";
    pmw = mainwindow;
}

void inplace(MainWindow* mainwindow){
    //接入到层
    HWND background = NULL;
    HWND hwnd = FindWindowA("progman","Program Manager");
    HWND worker = NULL;
    do{
        worker = FindWindowExA(NULL,worker,"WorkerW",NULL);
        if(worker!=NULL){
            char buff[200] = {0};

            int ret = GetClassName(worker,(WCHAR*)buff,sizeof(buff)*2);
            if(ret == 0){
                int err = GetLastError();
                qDebug()<<"err:"<<err;
            }
            //QString className = QString::fromUtf16((char16_t*)buff);
        }
        if(GetParent(worker) == hwnd){
            background = worker;
        }
    }while(worker !=NULL);
    SetParent((HWND)mainwindow->winId(),background);
}




