QT += sql
QT += core network

TARGET = Server
CONFIG += c++11 console
CONFIG -= app_bundle
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

VPATH += ./src

HEADERS += \
           include/dbworker.h \
           include/handlerbd.h \
           include/logincontroller.h \
           include/global.h \
           include/requestmapper.h \
           include/dumpcontroller.h \
           include/templatecontroller.h \
           include/formcontroller.h \
           include/fileuploadcontroller.h \
           include/sessioncontroller.h

SOURCES += src/main.cpp \
           dbworker.cpp \
           src/handlerbd.cpp \
           src/logincontroller.cpp \
           src/global.cpp \
           src/requestmapper.cpp \
           src/dumpcontroller.cpp \
           src/templatecontroller.cpp \
           src/formcontroller.cpp \
           src/fileuploadcontroller.cpp \
           src/sessioncontroller.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

OTHER_FILES += etc/* etc/docroot/* etc/templates/* etc/ssl/* logs/*

include(3drparty/QtWebApp/logging/logging.pri)
include(3drparty/QtWebApp/httpserver/httpserver.pri)
include(3drparty/QtWebApp/templateengine/templateengine.pri)
