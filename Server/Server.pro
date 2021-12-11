QT += sql
QT += core network

TARGET = Server
CONFIG += c++11 console
CONFIG -= app_bundle
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/src

HEADERS += \
           $$PWD/include/dbworker.h \
           $$PWD/include/handlerbd.h \
           $$PWD/include/logincontroller.h \
           $$PWD/include/global.h \
           $$PWD/include/requestmapper.h \
           $$PWD/include/dumpcontroller.h \
           $$PWD/include/serverapi.h \
           $$PWD/include/templatecontroller.h \
           $$PWD/include/formcontroller.h \
           $$PWD/include/fileuploadcontroller.h \
           $$PWD/include/sessioncontroller.h \
           $$PWD/include/clientapi.h \
           $$PWD/include/deliverapi.h \
           $$PWD/include/managerapi.h

SOURCES += \
           $$PWD/src/main.cpp\
           $$PWD/src/dbworker.cpp \
           $$PWD/src/handlerbd.cpp \
           $$PWD/src/logincontroller.cpp \
           $$PWD/src/global.cpp \
           $$PWD/src/requestmapper.cpp \
           $$PWD/src/dumpcontroller.cpp \
           $$PWD/src/templatecontroller.cpp \
           $$PWD/src/formcontroller.cpp \
           $$PWD/src/fileuploadcontroller.cpp \
           $$PWD/src/sessioncontroller.cpp \
           $$PWD/src/clientapi.cpp \
           $$PWD/src/deliverapi.cpp \
           $$PWD/src/managerapi.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

OTHER_FILES += etc/* etc/docroot/* etc/templates/* etc/ssl/* logs/*

include(../3rdparty/QtWebApp/QtWebApp/logging/logging.pri)
include(../3rdparty/QtWebApp/QtWebApp/httpserver/httpserver.pri)
include(../3rdparty/QtWebApp/QtWebApp/templateengine/templateengine.pri)
