#include<windows.h>
#include"mainwindow.h"
#include"mousehook.h"
#include"QTextCodec"
#include <QJsonObject>
#include<QDir>
#include<QFileInfo>
#include<QStandardPaths>
#include<QFileIconProvider>
#include<QIcon>
MainWindow* pmw;
MouseHook* pmh;
QTextCodec* utf8 = QTextCodec::codecForName("utf-8");
QTextCodec* gbk = QTextCodec::codecForName("GBK");


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
    // QTextCodec::setCodecForLocale(gbk);
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
    //定义返回的结构体
    QString name;
    QString filePath;
    QIcon icon;
};


QList<FileInfo> scandesktopfiles(const QString &desktopPath)
{
    //对于指定桌面路径，返还桌面路径中的文件信息的列表
    QList<FileInfo> files;
    QDir desktopDir(desktopPath);
    desktopDir.setFilter(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);
    QFileInfoList fileInfoList=desktopDir.entryInfoList();
    foreach(const QFileInfo &x,fileInfoList)
    {
        FileInfo file;
        file.filePath=x.absoluteFilePath();
        QString fileName = x.fileName();
        int lastDotIndex = fileName.lastIndexOf('.');
        if (lastDotIndex != -1)
        {
            fileName.remove(lastDotIndex, fileName.length() - lastDotIndex);
        }
        file.name=fileName;
        QFileIconProvider a;
        file.icon=a.icon(x);
        files.append(file);
    }
    return files;
}


QList<FileInfo> scanalldesktopfiles()
{
    //寻找桌面路径，并返回两个桌面中所有文件信息的列表
    QList<FileInfo> files;
    QString userdesktoppath=QDir::homePath()+"/Desktop";
    files.append(scandesktopfiles(userdesktoppath));
    QString publicdesktoppath=QDir::toNativeSeparators("C:/Users/Public/Desktop");
    files.append(scandesktopfiles(publicdesktoppath));
    return files;
}

QString GetCorrectUnicode(const QByteArray &ba)
{

    QTextCodec::ConverterState state;
    QTextCodec *codec = utf8;
    QString text = codec->toUnicode(ba.constData(), ba.size(), &state);
    if (state.invalidChars > 0)
    {
        qDebug()<<"GBK";
        text = gbk->toUnicode(ba);
    }
    else
    {
        qDebug()<<"utf-8";
        text = ba;
    }
    return text;
}

QString elidedLineText(QWidget *pWidget, int nLine, QString strText)
{
    if (nLine == 0)
        return "";

    QFontMetrics fontMetrics(pWidget->font());

    if (nLine == 1) {
        return fontMetrics.elidedText(strText, Qt::ElideRight, pWidget->width());
    }

    QStringList strListLine;

    for (int i = 0; i < strText.size(); i++)
    {
        if (fontMetrics.width(strText.left(i)) >= pWidget->width())
        {
            strListLine.append(strText.left(i));
            if (strListLine.size() == nLine)
            {
                break;
            }
            strText = strText.right(strText.size() - i);
            i = 0;
        }
    }

    if (strListLine.size() < nLine)
    {
        if (!strText.isEmpty()) {
            strListLine.append(strText);
        }
    }

    bool bHasElided = true;
    if (fontMetrics.width(strText) < pWidget->width())
    {
        bHasElided = false;
    }

    if (bHasElided && !strListLine.isEmpty())
    {
        QString strLast = strListLine.last();
        QString strElided = "...";
        strLast.insert(strLast.length(), strElided);
        while (fontMetrics.width(strLast) >= pWidget->width())
        {
            strLast = strLast.replace(0, 1, "");
        }

        strListLine.replace(strListLine.count() - 1, strLast);
    }
    QString strResult = strListLine.join("\n");

    return strResult;
}


