#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T15:41:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = smartHome
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    bedroomwidget.cpp \
    curtainwidget.cpp \
    musicwidget.cpp \
    modelchoosewidget.cpp \
    parlourwidget.cpp \
    kitchenwidget.cpp \
    systemsettingdialog.cpp \
    statisticwidget.cpp \
    qcustomplot.cpp

HEADERS  += widget.h \
    myhelp.h \
    bedroomwidget.h \
    curtainwidget.h \
    musicwidget.h \
    modelchoosewidget.h \
    parlourwidget.h \
    kitchenwidget.h \
    systemsettingdialog.h \
    statisticwidget.h \
    qcustomplot.h

FORMS    += widget.ui \
    bedroomwidget.ui \
    curtainwidget.ui \
    musicwidget.ui \
    modelchoosewidget.ui \
    parlourwidget.ui \
    kitchenwidget.ui \
    systemsettingdialog.ui \
    statisticwidget.ui

RESOURCES += \
    images.qrc
