#include "mainwindow.h"
#include<windows.h>
#include <QJsonObject>
#include <QApplication>
#include <QLocale>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Enhanced-desktop_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow mw ;
    //鼠标钩子
    // InitMouseHook();

    mw.show();
    return a.exec();
}
