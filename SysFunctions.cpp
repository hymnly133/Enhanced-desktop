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
    qDebug()<<"Initing";

    //无边框全屏
    mainwindow->setWindowState(Qt::WindowFullScreen);



    //无边框
    // mainwindow->setWindowFlags(Qt::FramelessWindowHint);



    //把窗口背景设置为透明
    // mainwindow->  setAttribute(Qt::WA_TranslucentBackground);


    //绑定函数


    qDebug()<<"Initing done";
    pmw = mainwindow;
}

void inplace(MainWindow* mainwindow) {
    // 接入到壁纸层
    HWND background = NULL;
    HWND hwnd = FindWindowA("Progman", "Program Manager");
    HWND worker = NULL;

    // 循环查找WorkerW窗口
    do {
        worker = FindWindowExA(NULL, worker, "WorkerW", NULL);
        if (worker != NULL) {
            // 尝试找到SHELLDLL_DefView窗口
            HWND shelldlldefview = FindWindowExA(worker, NULL, "SHELLDLL_DefView", NULL);
            if (shelldlldefview != NULL) {
                // 检查SHELLDLL_DefView的父窗口是否为当前的WorkerW窗口
                HWND parent = GetParent(shelldlldefview);
                if (parent == worker) {
                    // 找到了正确的WorkerW窗口
                    background = worker;
                    break; // 结束循环
                }
            }
        }
    } while (worker != NULL);

    // 如果找到了正确的WorkerW窗口，设置父窗口
    if (background != NULL) {
        SetParent((HWND)mainwindow->winId(), background);
        // 将MainWindow_E窗口置于SHELLDLL_DefView窗口上方
        SetWindowPos((HWND)mainwindow->winId(), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        // 设置MainWindow_E窗口为顶层窗口，以便接收点击事件
        SetWindowPos((HWND)mainwindow->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        // 确保MainWindow_E窗口可以获得焦点
        SetFocus((HWND)mainwindow->winId());
    } else {
        // 如果没有找到合适的WorkerW窗口，可以在这里处理错误
        qDebug() << "未能找到合适的WorkerW窗口";
    }
}


