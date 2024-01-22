QT += core

TEMPLATE = lib
DEFINES += NAMEOF_LIBRARY

CONFIG += c++14
msvc:QMAKE_CXXFLAGS += /std:c++17

DEFINES += NAMEOF_LIBRARY

include($$PWD/../../libinstall/common.prf)

HEADERS += \
    nameof.h \
    nameof_global.h

SOURCES += \
    nameof.cpp \

include($$PWD/../../libinstall/libinstall.prf)
