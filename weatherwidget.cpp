#include "weatherwidget.h"
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
#include <QMessageBox>
#include <QUrlQuery>
#include"QDesktopServices"
#include"QTextCodec"
#include "qpainter.h"
#include"QGraphicsDropShadowEffect"
WEATHERWIDGET::WEATHERWIDGET(QWidget *parent, int sizex, int sizey)
    : ED_Unit(parent,sizex,sizey)
{
    type = Unit;
    wlayout=new QVBoxLayout(this);
    manager=new QNetworkAccessManager(this);
    temperatureLabel=new QLabel(this);
    weatherlabel=new QLabel(this);
    advicelabel=new QLabel(this);
    wlayout->addWidget(temperatureLabel, 0, Qt::AlignHCenter);
    wlayout->addWidget(weatherlabel, 0, Qt::AlignHCenter);
    wlayout->addWidget(advicelabel, 0, Qt::AlignHCenter);
    connect(manager,&QNetworkAccessManager::finished,this,&WEATHERWIDGET::handleWeatherResponse);
    addWeatherInfo("101010200");
    setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction* act1  = new QAction("加宽");
    this->addAction(act1);
    connect(act1, &QAction::triggered, this, [=]()
            {
                setBlockSize(sizeX+1,sizeY);
            });

    QAction* act3  = new QAction("减宽");
    this->addAction(act3);
    connect(act3, &QAction::triggered, this, [=]()
            {
                if(sizeX>=2)
                    setBlockSize(sizeX-1,sizeY);
            });

    QAction* act2  = new QAction("加高");
    this->addAction(act2);
    connect(act2, &QAction::triggered, this, [=]()
            {
                setBlockSize(sizeX,sizeY+1);
            });



    QAction* act4  = new QAction("减高");
    this->addAction(act4);
    connect(act4, &QAction::triggered, this, [=]()
            {
                if(sizeY>=2)
                    setBlockSize(sizeX,sizeY-1);
            });

}



void WEATHERWIDGET::addWeatherInfo(QString citycode)
{
    QUrl url("http://t.weather.itboy.net/api/weather/city/"+citycode);
    manager->get(QNetworkRequest(url));
}

void WEATHERWIDGET::handleWeatherResponse(QNetworkReply *reply)
{
    //qDebug()<<"success";
    int statuscode=reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    //qDebug()<<statuscode;
    QByteArray byteArray=reply->readAll();
    //qDebug()<<byteArray.data();
    parsejson(byteArray);
}

void WEATHERWIDGET::double_click_action(){
    //qDebug() <<"wearther";
    emit sendSelf();
    addWeatherInfo("101010200");
}

void WEATHERWIDGET::parsejson(QByteArray &byteArray)
{
    QJsonParseError err;
    QJsonDocument doc=QJsonDocument::fromJson(byteArray,&err);
    QJsonObject rootobj=doc.object();
    QJsonObject dataobj=rootobj.value("data").toObject();
    temperatureLabel->setText("北京海淀区气温" + rootobj.value("data").toObject().value("wendu").toString() + " °C");
    weatherlabel->setText("空气污染："+rootobj.value("data").toObject().value("quality").toString());
    advicelabel->setText("建议："+rootobj.value("data").toObject().value("ganmao").toString());

}


