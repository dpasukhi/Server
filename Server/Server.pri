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
           $$PWD/include/sessioncontroller.h

SOURCES += \
           $$PWD/src/dbworker.cpp \
           $$PWD/src/handlerbd.cpp \
           $$PWD/src/logincontroller.cpp \
           $$PWD/src/global.cpp \
           $$PWD/src/requestmapper.cpp \
           $$PWD/src/dumpcontroller.cpp \
           $$PWD/src/serverapi.cpp \
           $$PWD/src/templatecontroller.cpp \
           $$PWD/src/formcontroller.cpp \
           $$PWD/src/fileuploadcontroller.cpp \
           $$PWD/src/sessioncontroller.cpp
