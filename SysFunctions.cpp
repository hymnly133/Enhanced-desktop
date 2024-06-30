#include<windows.h>
#include"mainwindow.h"
#include"mousehook.h"
#include"SysFunctions.h"
#include"QTextCodec"
#include "qpainter.h"
#include <QJsonObject>
#include<QDir>
#include<QFileInfo>
#include<QStandardPaths>
#include<QFileIconProvider>
#include<QSettings>
#include<QIcon>
MainWindow* pmw;;
MouseHook* pmh;
QTextCodec* utf8 = QTextCodec::codecForName("utf-8");
QTextCodec* gbk = QTextCodec::codecForName("GBK");


QRect AbsoluteRect(QWidget* aim){
    auto tem = aim->geometry();
    auto pos = aim->parentWidget()->pos();
    return QRect(pos.x()+tem.x(),pos.y()+tem.y(),tem.width(),tem.height());
}

void paintRect(QWidget* aim,QColor color){
    bool another = true;
    bool choosen = false;
    if(aim->inherits("ED_Unit")) {
        another = ((ED_Unit*)aim)->showRect;
        choosen = ((ED_Unit*)aim)->onmouse;
    }
    if(ShowRect&(another)){
        QPainter paint(aim);
        paint.fillRect(aim->rect(),color);
    }
}

void paintLight(QWidget* aim,QColor color){
    bool another = true;
    bool choosen = false;
    if(aim->inherits("ED_Unit")) {
        another = ((ED_Unit*)aim)->showRect;
        choosen = ((ED_Unit*)aim)->onmouse;
    }
    if(aim->inherits("ED_Unit")) another = ((ED_Unit*)aim)->showLight;
    if(ShowLight&(another)){
        color.setAlpha(light_alpha_start);
        auto pos =aim->mapFromGlobal(aim->cursor().pos());
        QRadialGradient* radialGradient;
        if(enable_light_track){
            radialGradient = new QRadialGradient(aim->width()/2 , aim->height()/2, qMax(aim->width(),aim->height()),pos.x() ,pos.y());
        }
        else{
            radialGradient = new QRadialGradient(aim->width()/2 , aim->height()/2, qMax(aim->width(),aim->height()),0, aim->height());
        }
        //创建了一个QRadialGradient对象实例，参数分别为中心坐标，半径长度和焦点坐标,如果需要对称那么中心坐标和焦点坐标要一致
        QPainter painter(aim);
        painter.setPen(Qt::NoPen);
        radialGradient->setColorAt(0,color);
        color.setAlpha(light_alpha_end);
        radialGradient->setColorAt(1.0,color);
        painter.setBrush(QBrush(*radialGradient));
        painter.drawRect(aim->rect());//在相应的坐标画出来
    }
}

void paintSide(QWidget* aim,QColor color){
    bool another = true;
    if(aim->inherits("ED_Unit")) another = ((ED_Unit*)aim)->showSide;
    if(ShowSide&another){
        QPainter p(aim);
        p.setPen(color); //设置画笔记颜色
        p.drawRect(0, 0, aim->width() -1, aim->height() -1); //绘制边框
    }
}

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
    mainwindow->setAttribute(Qt::WA_TranslucentBackground);
    // mainwindow-> setWindowFlags(Qt::FramelessWindowHint);

    //注入壁纸
    inplace((QWidget* )mainwindow);
    qDebug()<<"Initing done";
    pmw = mainwindow;
}



void inplace(QWidget* aim) {
    // 接入到图标层
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
        SetParent((HWND)aim->winId(), background);
        SetWindowPos((HWND)aim->winId(), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        SetWindowPos((HWND)aim->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        SetFocus((HWND)aim->winId());
    } else {
        // 如果没有找到合适的WorkerW窗口，可以在这里处理错误
        qDebug() << "未能找到合适的WorkerW窗口";
    }
}

void inplace2(QWidget* pmw2) {
    // 接入到壁纸层
    HWND background = NULL;
    HWND hwnd = FindWindowA("Progman", "Program Manager");
    HWND worker = NULL;

    // 循环查找WorkerW窗口
    do
    {
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
    SetParent((HWND)pmw2->winId(),background);

    // 如果找到了符合条件的 WorkerW 窗口，设置 Qt 窗口的父窗口
}

QList<FileInfo> scandesktopfiles(const QString &desktopPath)
{
    //对于指定桌面路径，返还桌面路径中的文件信息的列表
    QList<FileInfo> files;
    QDir desktopDir(desktopPath);
    desktopDir.setFilter(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);
    QFileInfoList fileInfoList=desktopDir.entryInfoList();
    foreach(const QFileInfo &x,fileInfoList)
    {
        FileInfo file;;
        file.type = FileInfo::NORM;
        file.filePath=x.absoluteFilePath();
        QString fileName = x.fileName();
        int lastDotIndex = fileName.lastIndexOf('.');
        if (lastDotIndex != -1)
        {
            fileName.remove(lastDotIndex, fileName.length() - lastDotIndex);
        }
        file.name=fileName;
        qDebug()<<x.suffix().toLower()<<x.symLinkTarget();
        if (x.suffix().toLower() == "lnk")
        {
            // 处理快捷方式（.lnk 文件）
            QString target = x.symLinkTarget();
            if (!target.isEmpty())
            {

                QDir targetDir(QFileInfo(target).absolutePath());
                QStringList iconFiles = targetDir.entryList(QStringList() << "*.ico", QDir::Files);
                if (!iconFiles.isEmpty())
                {
                    file.icon = QIcon(targetDir.absoluteFilePath(iconFiles.first())); // 或者根据需要设置其他类型
                }
                if(file.icon.isNull())
                {
                    QFileIconProvider iconProvider;
                    file.icon =iconProvider.icon(QFileInfo(target));
                }
            }
        }
        else
        {
            QFileIconProvider a;
            file.icon = a.icon(x);
        }
        //针对steam游戏
        QSettings shortcut(x.filePath(), QSettings::IniFormat);
        QString target = shortcut.value("InternetShortcut/URL").toString();
        QRegularExpression re("steam://rungameid/(\\d+)");
        QRegularExpressionMatch match = re.match(target);
        if (match.hasMatch())
        {
            QString gameId = match.captured(1);
            //QString steamPath = "C:/Program Files (x86)/Steam/appcache/librarycache"; // 你的Steam安装路径
            QString steamPath;
            QSettings reg("HKEY_CURRENT_USER\\Software\\Valve\\Steam", QSettings::NativeFormat);
            steamPath = reg.value("SteamPath").toString()+"/appcache/librarycache";
            QStringList result;
            QDir directory(steamPath);
            QStringList steamfileList=directory.entryList(QDir::Files);

            QRegularExpression regex(gameId+"_library");
            //长竖图标版本
            steamfileList=directory.entryList(QDir::Files);
            foreach(const QString& steamfilename,steamfileList)
            {
                if(regex.match(steamfilename).hasMatch())
                {
                    file.icon=QIcon(directory.absoluteFilePath(steamfilename));
                    file.type = FileInfo::HORI;
                    files.append(file);
                }
            }


            regex = QRegularExpression(gameId+"_header");
            //长横图标版本
            steamfileList=directory.entryList(QDir::Files);
            foreach(const QString& steamfilename,steamfileList)
            {
                if(regex.match(steamfilename).hasMatch())
                {
                    file.icon=QIcon(directory.absoluteFilePath(steamfilename));
                    file.type = FileInfo::VERT;
                    files.append(file);

                }
            }


            regex = QRegularExpression(gameId+"_icon");
            //小图标版本
            foreach(const QString& steamfilename,steamfileList)
            {
                if(regex.match(steamfilename).hasMatch())
                {
                    result.append(directory.absoluteFilePath(steamfilename));
                    file.icon=QIcon(directory.absoluteFilePath(steamfilename));
                    file.type = FileInfo::NORM;
                }
            }
        }
        //以上为针对steam游戏
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
    //调整输出
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


QColor pixmapMainColor(QPixmap p, double bright) //p为目标图片 bright为亮度系数，为1则表示保持不变
{
    int step=20; //步长：在图片中取点时两点之间的间隔，若为1,则取所有点，适当将此值调大有利于提高运行速度
    int t=0; //点数：记录一共取了多少个点，用于做计算平均数的分母
    QImage image=p.toImage(); //将Pixmap类型转为QImage类型
    int r=0,g=0,b=0; //三元色的值，分别用于记录各个点的rgb值的和
    for (int i=0;i<p.width();i+=step) {
        for (int j=0;j<p.height();j+=step) {
            if(image.valid(i,j)){ //判断该点是否有效
                t++; //点数加一
                QColor c=image.pixel(i,j); //获取该点的颜色
                r+=c.red(); //将获取到的各个颜色值分别累加到rgb三个变量中
                b+=c.blue();
                g+=c.green();
            }
        }
    }
    return QColor(int(bright*r/t)>255?255:int(bright*r/t),
                  int(bright*g/t)>255?255:int(bright*g/t),
                  int(bright*b/t)>255?255:int(bright*b/t)); //最后返回的值是亮度系数×平均数,若超出255则设置为255也就是最大值，防止乘与亮度系数后导致某些值大于255的情况。
}

void repaintAround(QWidget* aim){
    auto tem = aim->geometry();
    auto rrect = QRect(tem.x()-100,tem.y()-100,tem.width()+200,tem.height()+200);
    pmw->repaint(rrect);

}
