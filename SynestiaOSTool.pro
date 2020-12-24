QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SerialPortReader.cpp \
    aboutdialog.cpp \
    downloadtool.cpp \
    main.cpp \
    osmonitor.cpp \
    serialtool.cpp \
    synestiatool.cpp

HEADERS += \
    SerialPortReader.h \
    aboutdialog.h \
    downloadtool.h \
    osmonitor.h \
    serialtool.h \
    synestiatool.h

FORMS += \
    aboutdialog.ui \
    downloadtool.ui \
    osmonitor.ui \
    serialtool.ui \
    synestiatool.ui

TRANSLATIONS += \
    SynestiaOSTool_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
