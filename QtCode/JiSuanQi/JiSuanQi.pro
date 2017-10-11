#-------------------------------------------------
#
# Project created by QtCreator 2017-09-21T11:20:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JiSuanQi
TEMPLATE = app

include(common.pri)

RC_FILE = myapp.rc

SOURCES += main.cpp\
        widget.cpp \
    main_window.cpp \
    titlebar.cpp \
    simple_mode.cpp \
    simple_button.cpp \
    simple_edit.cpp \
    scientific_mode.cpp \
    sc_button.cpp \
    sc_edit.cpp \
    result_display.cpp \
    mybasedialog.cpp

HEADERS  += widget.h \
    main_window.h \
    titlebar.h \
    simple_mode.h \
    simple_button.h \
    simple_edit.h \
    scientific_mode.h \
    sc_button.h \
    sc_edit.h \
    result_display.h \
    mybasedialog.h

RESOURCES += \
    calculator.qrc
