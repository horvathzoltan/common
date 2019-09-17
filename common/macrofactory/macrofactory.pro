QT += core

TEMPLATE = lib

CONFIG += c++1z
QMAKE_CXXFLAGS += /std:c++17

DEFINES += MACROFACTORY_LIBRARY

include($$PWD/../../libinstall/common.prf)

HEADERS += \
    macro.h \
    zlogicexception.h \
    zlogicexpression_global.h

SOURCES += \
    zlogicexception.cpp

include($$PWD/../../libinstall/libinstall.prf)
