#-------------------------------------------------
#
# Project created by QtCreator 2017-10-19T09:47:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mymainwindow.cpp \
    mytitlebar.cpp \
    mytoolbar.cpp \
    mytoolbtn.cpp \
    mybasedialog.cpp \
    mycontentwidget.cpp \
    widget1.cpp

HEADERS  += widget.h \
    mymainwindow.h \
    mytitlebar.h \
    mytoolbar.h \
    mytoolbtn.h \
    mybasedialog.h \
    mycontentwidget.h \
    widget1.h

FORMS    += widget.ui \
    widget1.ui

RESOURCES += \
    resource.qrc

RC_FILE = myapp.rc
