TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread

QT += sql
QT += core network
QT += widgets
HEADERS += \
        tst_servertest.h

SOURCES += \
        main.cpp

include(../Server/Server.pri)
include(../3rdparty/QtWebApp/QtWebApp/logging/logging.pri)
include(../3rdparty/QtWebApp/QtWebApp/httpserver/httpserver.pri)
include(../3rdparty/QtWebApp/QtWebApp/templateengine/templateengine.pri)
include(gtest_dependency.pri)
