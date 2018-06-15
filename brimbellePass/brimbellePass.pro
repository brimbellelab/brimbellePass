#-------------------------------------------------
#
# Project created by QtCreator 2018-04-18T14:14:29
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += "/usr/local/opt/openssl/include/"

LIBS += -L"/usr/local/opt/openssl/lib" -lcrypto

macx{
ICON = brimbellePass.icns
}

test {
    message("Test build")
    QT += testlib
    TARGET = UnitTests

    SOURCES += tests/testcipher.cpp \
    tests/testaccountsbook.cpp \
    tests/testmain.cpp

    HEADERS += tests/testcipher.h \
    tests/testaccountsbook.h
} else {
    message("Normal build")
    TARGET = brimbellePass
    SOURCES += main.cpp
}

SOURCES += mainwindow.cpp \
    displayentrytab.cpp \
    displayentrycontent.cpp \
    passwordentryline.cpp \
    addentrytab.cpp \
    configurationtab.cpp \
    account.cpp \
    accountsbook.cpp \
    xmldom.cpp \
    xmlinputfilesource.cpp \
    configfile.cpp \
    cipher.cpp \
    infotab.cpp \
    safetyqawidget.cpp \
    dialogaddsafetyqa.cpp \
    dialognewpassword.cpp

HEADERS  += mainwindow.h \
    displayentrytab.h \
    displayentrycontent.h \
    passwordentryline.h \
    addentrytab.h \
    configurationtab.h \
    account.h \
    accountsbook.h \
    xmldom.h \
    xmlinputfilesource.h \
    configfile.h \
    cipher.h \
    infotab.h \
    safetyqawidget.h \
    dialogaddsafetyqa.h \
    dialognewpassword.h

RESOURCES += \
    resources.qrc

