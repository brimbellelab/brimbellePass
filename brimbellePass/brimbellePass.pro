#-------------------------------------------------
#
# Project created by QtCreator 2018-04-18T14:14:29
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = brimbellePass
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    displayentrytab.cpp \
    displayentrycontent.cpp \
    passwordentryline.cpp \
    addentrytab.cpp \
    configurationtab.cpp \
    account.cpp \
    accountsbook.cpp \
    xmldom.cpp

HEADERS  += mainwindow.h \
    displayentrytab.h \
    displayentrycontent.h \
    passwordentryline.h \
    addentrytab.h \
    configurationtab.h \
    account.h \
    accountsbook.h \
    xmldom.h

RESOURCES += \
    resources.qrc
