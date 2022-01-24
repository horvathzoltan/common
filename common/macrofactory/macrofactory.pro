QT += core

TEMPLATE = lib

CONFIG += c++14
msvc:QMAKE_CXXFLAGS += /std:c++17

DEFINES += MACROFACTORY_LIBRARY

include($$PWD/../../libinstall/common.prf)

HEADERS += \
    macro.h \
    stringliteral2.h \
    zlogicexception.h \
    zlogicexpression_global.h

SOURCES += \
    zlogicexception.cpp

include($$PWD/../../libinstall/libinstall.prf)
