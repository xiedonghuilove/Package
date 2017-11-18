#-------------------------------------------------
#
# Project created by QtCreator 2016-09-29T15:48:03
#
#-------------------------------------------------

QT       += core gui network sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET              = API
TEMPLATE            = app
MOC_DIR             = temp/moc
RCC_DIR             = temp/rcc
UI_DIR              = temp/ui
OBJECTS_DIR         = temp/obj
DESTDIR             = bin
win32:RC_FILE       = main.rc

include($$PWD/api/api.pri)

SOURCES += main.cpp\
        frmapi.cpp \
    frmntpapi.cpp \
    frmapplog.cpp \
    frmledapi.cpp \
    frmframeless.cpp

HEADERS  += myhelper.h \
        frmapi.h \
    frmntpapi.h \
    frmapplog.h \
    frmledapi.h \
    frmframeless.h

FORMS    += frmapi.ui \
    frmntpapi.ui \
    frmapplog.ui \
    frmledapi.ui \
    frmframeless.ui

RESOURCES += \
    main.qrc

CONFIG += qt warn_off release
