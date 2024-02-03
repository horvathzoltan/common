QT += core

TEMPLATE = lib
DEFINES += COM_NAMEOF_LIBRARY

CONFIG += c++14
msvc:QMAKE_CXXFLAGS += /std:c++17


include($$PWD/../../libinstall/common.prf)

HEADERS += \
    nameof.h \
    nameof_global.h

SOURCES += \
    nameof.cpp \

include($$PWD/../../libinstall/libinstall.prf)
