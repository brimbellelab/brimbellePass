#-------------------------------------------------
#
# Project created by QtCreator 2018-04-18T14:14:29
#
#-------------------------------------------------

message(===============================)

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#Application version
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_PATCH = 0

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
           "VERSION_MINOR=$$VERSION_MINOR"\
           "VERSION_PATCH=$$VERSION_PATCH"

#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}
message(Building v$$VERSION)

TEMPLATE = app
CONFIG += c++11

unix{
message("Plateform is UNIX")
INCLUDEPATH += "/usr/local/opt/openssl/include/"
LIBS += -L"/usr/local/opt/openssl/lib" -lcrypto
}

win32{
message("Plateform is Win32")
INCLUDEPATH += C:/Openssl-Win32/include/
LIBS += -LC:/Openssl-Win32/lib/MinGW -lcrypto-1_1
}

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
    dialognewpassword.cpp \
    dialognewdatabase.cpp \
    filepathfinder.cpp \
    newpasswordwidget.cpp \
    dialogopendatabase.cpp

HEADERS  += mainwindow.h \
    displayentrytab.h \
    displayentrycontent.h \
    passwordentryline.h \
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
    dialognewpassword.h \
    dialognewdatabase.h \
    filepathfinder.h \
    newpasswordwidget.h \
    dialogopendatabase.h \
    brimbellepasserror.h

RESOURCES += \
    resources.qrc

