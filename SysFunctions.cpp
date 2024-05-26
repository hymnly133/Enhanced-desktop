#include<windows.h>
#include"mainwindow.h"
#include <QJsonObject>

void Init(MainWindow* mainwindow){


    // mainwindow->setWindowState(Qt::WindowFullScreen);
mainwindow->setWindowFlags(Qt::FramelessWindowHint);
    qDebug()<<"showing";
}

void inplace(MainWindow* mainwindow){
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
// mouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),NULL);//注册鼠标钩子

// LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam )
// {
//     if(nCode == HC_ACTION) //当nCode等于HC_ACTION时，要求得到处理
//     {
//         if(wParam==WM_MOUSEMOVE)//鼠标的移动
//         {
//             POINT p;
//             GetCursorPos(&p);//获取鼠标坐标
//             CMask* mask = w->getMask();
//             mask->setMask(p.x,p.y);
//             //双薪壁纸
//             mask->update();
//         }
//     }
//     //qDebug()<<nCode<<","<<wParam<<","<<lParam;
//     return CallNextHookEx(mouseHook,nCode,wParam,lParam);//返回给下一个钩子子程处理
// }
