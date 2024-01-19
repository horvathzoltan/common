QT -= gui

TARGET = processhelper

TEMPLATE = lib
DEFINES += COM_PROCESSHELPER_LIBRARY

#CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    processhelper.cpp

HEADERS += \
    ProcessHelper_global.h \
    processhelper.h

CONFIG += c++14
msvc:QMAKE_CXXFLAGS += /std:c++17

include($$PWD/../../../libinstall//common.prf)

unix:!macx:
{
LIBS += -L$$HOME/$$COMMON_LIBS/ -llogger
}

win32:
{
WINLIBS = $$system_path($$HOME/$$COMMON_LIBS/)
LIBS += -L$$WINLIBS -lmacrofactory -llogger
}

include($$PWD/../../../libinstall//libinstall.prf)
