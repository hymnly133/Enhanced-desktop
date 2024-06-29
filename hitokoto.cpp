#include "hitokoto.h"
#include "QWidget"
#include"QProcess"
#include "qaction.h"
#include "qboxlayout.h"
#include"SysFunctions.h"
#include "qlabel.h"
#include"QDebug"
#include"QUrl"
#include <QJsonDocument>
#include <QJsonObject>
#include "QtNetwork/QHttpMultiPart"
#include "QHttpMultiPart"
#include <QMessageBox>
#include <QUrlQuery>
#include"QDesktopServices"
#include"QTextCodec"
#include "qpainter.h"
#include"QGraphicsDropShadowEffect"

Hitokoto::Hitokoto(QWidget *parent,int sizex,int sizey)
    : ED_Unit(parent,sizex,sizey)
{
    wlayout=new QVBoxLayout(this);
    manager=new QNetworkAccessManager(this);
    hitokotolabel=new QLabel(this);
    wlayout->addWidget(hitokotolabel, 0, Qt::AlignHCenter);
    connect(manager,&QNetworkAccessManager::finished,this,&Hitokoto::handlehitokotoresponse);
    gethitokotoinfo();
}

void Hitokoto::gethitokotoinfo()
{
    QUrl url("https://www.juhe.cn/docs/api/id/63");
    manager->get(QNetworkRequest(url));
}

void Hitokoto::handlehitokotoresponse(QNetworkReply *reply)
{
    qDebug()<<"success";
    int statuscode=reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug()<<statuscode;
    QByteArray byteArray=reply->readAll();
    qDebug()<<byteArray.data();
    parsejson(byteArray);
}

void Hitokoto::parsejson(QByteArray &byteArray)
{
    QJsonParseError err;
    QJsonDocument doc=QJsonDocument::fromJson(byteArray,&err);
}
