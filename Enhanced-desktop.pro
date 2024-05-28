QT       += core gui

win32 {
LIBS+= -luser32    # 使用WindowsAPI需要链接库
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SysFunctions.cpp \
    card.cpp \
    ed_block.cpp \
    main.cpp \
    mainwindow.cpp \
    mousehook.cpp \
    mylineedit.cpp

HEADERS += \
    SysFunctions.h \
    card.h \
    ed_block.h \
    mainwindow.h \
    mousehook.h \
    mylineedit.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Enhanced-desktop_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
