#include<windows.h>
#include"mainwindow.h"
#include"mousehook.h"
#include <QJsonObject>
MainWindow* pmw;
MouseHook* pmh;
//主窗口指针

void mouse_move(int x,int y){

    qDebug()<<"move"<<x<<y;
    // pmw->move(x,y);
}
void mouse_on(int x,int y){

    qDebug()<<"on"<<x<<y;
}
void mouse_off(int x,int y){

    qDebug()<<"off"<<x<<y;
}
void InitMouseHook(){
    pmh = new MouseHook();
    pmh->SetMouseMoveCallBack(mouse_move);
    pmh->SetMouseOffCallBack(mouse_off);
    pmh->SetMouseOnCallBack(mouse_on);
}
void Init(MainWindow* mainwindow){
    //初始化


    // mainwindow->setWindowState(Qt::WindowFullScreen);
        qDebug()<<"Initing";
    //无边框
    mainwindow->setWindowFlags(Qt::FramelessWindowHint);

    //把窗口背景设置为透明
    // mainwindow->  setAttribute(Qt::WA_TranslucentBackground);

    //绑定函数


    qDebug()<<"Initing done";
    pmw = mainwindow;
}

void inplace(MainWindow* mainwindow){
    //接入到壁纸层
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




