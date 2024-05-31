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
    block_container.cpp \
    ed_block.cpp \
    ed_hidetextblock.cpp \
    ed_layout.cpp \
    ed_unit.cpp \
    main.cpp \
    mainwindow.cpp \
    mousehook.cpp \
    picturebox.cpp

HEADERS += \
    SysFunctions.h \
    block_container.h \
    ed_block.h \
    ed_hidetextblock.h \
    ed_layout.h \
    ed_unit.h \
    mainwindow.h \
    mousehook.h \
    picturebox.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Enhanced-desktop_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations


# TEMPLATE = subdirs

SUBDIRS += \
    ContextMenu/ContextMenu.pro

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# DISTFILES += \
#     ContextMenu/ContextMenu.pro.user

RESOURCES += \
    res.qrc

