#-------------------------------------------------
#
# Project created by QtCreator 2015-08-14T12:57:48
#
#-------------------------------------------------

QT       += core gui network script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = Rythem2015
TEMPLATE = app


CONFIG += debug_and_release

CONFIG(debug, debug|release) {
    win32: TARGET = $$join(TARGET,,,d)
}
SOURCES += main.cpp\
        mainwindow.cpp \
    rythemapp.cpp \
    ryproxyserver.cpp \
    ryconnection.cpp \
    ryhttpparser.cpp

HEADERS  += mainwindow.h \
    rythemapp.h \
    singleapp.h \
    ryproxyserver.h \
    ryconnection.h \
    ryhttpparser.h

FORMS    += mainwindow.ui

