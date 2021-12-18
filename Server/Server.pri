INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/src

HEADERS += \
          $$PWD/include/dbworker.h \
          $$PWD/include/handlerbd.h \
          $$PWD/include/global.h \
          $$PWD/include/requestmapper.h \
          $$PWD/include/delivercontroller.h \
          $$PWD/include/managercontroller.h \
          $$PWD/include/customercontroller.h

SOURCES += \
          $$PWD/src/dbworker.cpp \
          $$PWD/src/handlerbd.cpp \
          $$PWD/src/global.cpp \
          $$PWD/src/requestmapper.cpp \
          $$PWD/src/delivercontroller.cpp \
          $$PWD/src/managercontroller.cpp \
          $$PWD/src/customercontroller.cpp
