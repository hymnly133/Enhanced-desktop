#include<windows.h>
#include"mainwindow.h"
#include"mousehook.h"
#include <QJsonObject>
#include<QDir>
#include<QFileInfo>
#include<QStandardPaths>
#include<QFileIconProvider>
#include<QIcon>
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

void inplace() {
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
        SetParent((HWND)pmw->winId(), background);
        SetWindowPos((HWND)pmw->winId(), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        SetWindowPos((HWND)pmw->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        SetFocus((HWND)pmw->winId());
    } else {
        // 如果没有找到合适的WorkerW窗口，可以在这里处理错误
        qDebug() << "未能找到合适的WorkerW窗口";
    }
}

struct FileInfo
{
    QString name;
    QString filePath;
    QIcon icon;
};
//定义返回的结构体

QList<FileInfo> scandesktopfiles(const QString &desktopPath)
{
    QList<FileInfo> files;
    QDir desktopDir(desktopPath);
    desktopDir.setFilter(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);
    QFileInfoList fileInfoList=desktopDir.entryInfoList();
    foreach(const QFileInfo &x,fileInfoList)
    {
        FileInfo file;
        file.filePath=x.absoluteFilePath();
        file.name=x.fileName();
        QFileIconProvider a;
        file.icon=a.icon(x);
        files.append(file);
    }
    return files;
}
//对于指定桌面路径，返还桌面路径中的文件信息的列表

QList<FileInfo> scanalldesktopfiles()
{
    QList<FileInfo> files;
    QString userdesktoppath=QDir::homePath()+"/Desktop";
    files.append(scandesktopfiles(userdesktoppath));
    QStringList desktoppaths=QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
    QString publicdesktoppath;
    if(desktoppaths.count()>1)
    {
        publicdesktoppath=desktoppaths.at(1);
        files.append(scandesktopfiles(publicdesktoppath));
    }
    return files;
}
//寻找桌面路径，并返回两个桌面中所有文件信息的列表
