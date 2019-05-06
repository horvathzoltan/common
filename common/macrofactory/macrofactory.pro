QT += core

TEMPLATE = lib

HEADERS += \
    macro.h \
    zlogicexception.h

SOURCES += \
    zlogicexception.cpp

include($$PWD/../../libinstall/libinstall.prf)
