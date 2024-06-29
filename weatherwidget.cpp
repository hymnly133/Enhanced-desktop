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
    wlayout->addWidget(temperatureLabel, 0, Qt::AlignHCenter);
    connect(manager,&QNetworkAccessManager::finished,this,&WEATHERWIDGET::handleWeatherResponse);
    addWeatherInfo("101010100");
}



void WEATHERWIDGET::addWeatherInfo(QString citycode)
{
    QUrl url("http://t.weather.itboy.net/api/weather/city/"+citycode);
    manager->get(QNetworkRequest(url));
}

void WEATHERWIDGET::handleWeatherResponse(QNetworkReply *reply)
{
    qDebug()<<"success";
    int statuscode=reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug()<<statuscode;
    QByteArray byteArray=reply->readAll();
    qDebug()<<byteArray.data();
    parsejson(byteArray);
}

void WEATHERWIDGET::double_click_action(){
    qDebug() <<"wearther";
    emit sendSelf();
    addWeatherInfo("101010100");
}

void WEATHERWIDGET::parsejson(QByteArray &byteArray)
{
    QJsonParseError err;
    QJsonDocument doc=QJsonDocument::fromJson(byteArray,&err);
    QJsonObject rootobj=doc.object();
    QJsonObject dataobj=rootobj.value("data").toObject();
    temperatureLabel->setText("北京" + rootobj.value("data").toObject().value("wendu").toString() + " °C");


}
