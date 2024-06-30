#ifndef WEATHER_H
#define WEATHER_H

#include<QWidget>
#include"ed_unit.h"
#include<QLabel>
#include<QVBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>


class Weather : public ED_Unit
{
    Q_OBJECT
public:
    explicit Weather(QWidget *parent = nullptr,int sizex=1,int sizey=1);
    QLabel *temperatureLabel;
    QLabel *weatherlabel;
    QLabel *advicelabel;
    QNetworkAccessManager *manager;
    QVBoxLayout *wlayout;
    void addWeatherInfo(QString citycode);
    void double_click_action() override;
    void parsejson(QByteArray& byteArray);
signals:
    void sendSelf();
private slots:
    void handleWeatherResponse(QNetworkReply *reply);

};

#endif // WEATHER_H
